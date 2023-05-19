#  A simple service example: `AtomicNumberService`  {#AtomicNumber_README}

| Example name:   | AtomicNumber                          |
| --------------- | ------------------------------------- |
| Type:           | LArSoft service and provider          |
| Author:         | Gianluca Petrillo (petrillo@fnal.gov) |
| Created on:     | April 13, 2016                        |


This example shows a complete service with a minimal interface.

Features of the service:

* the interface returns a single quantity: the atomic number of the active
  material in the TPC
* reads the configuration from a FHiCL file
* provides a "standard" FHiCL configuration

Missing features that you need to go elsewhere if you need to implement:

* multiple implementation (for example, for different detectors)
* reaction to framework events (new event, end of run, closing input file...)
* integration test
* extension of LArSoft test utilities to easily have this provider in unit tests

Technical choices:

* employs the service/provider factorisation model
* uses validation of the configuration
* has four tests (three for the provider and one for the service)
* it is fully documented via Doxygen interpreted comments


### How to use this document                                                 ###

This document is pretty long. You are encouraged to read it all, but you might
understandably opt out of that.
The document is organised in sections. We suggest that you read the section
above to know what this example is about, and the (very terse) explanation of
the model, and the beginning of the section of the provider header.
These contain information about the design that can stimulate your own.
Then, you can dig into the code and come back to the pertinent section when you
have questions.

For every questions, answered or not here, you are strongly encouraged to
contact the example's author (contact information is at the top of this file).

And, if you want to have a bit more printer friendly format, know this text file
is written in markdown format and you can convert it to something else with:
    
    pandoc -s -S --toc -o README.html README.md
    pandoc -s -S --toc -o README.pdf README.md
    
et cetera.



## The factorisation model for services  #######################################

The factorisation model prescribes the code to be split in a functional part
that is independent of the framework, and a framework interface.

In case of services, LArSoft calls the functional part a _service provider_
(or just _provider_) and the interface a _art service_ (sometimes just
_service_).

A more extensive description of this model can be found in [LArSoft wiki].



## Files  ######################################################################

The example is split between two directories:

~~~~
larexamples/Services/AtomicNumber/         ### contains all the service code ###
|-- README                                                          # this file
|-- Providers                                        ## service provider code ##
|   |-- AtomicNumber.h                        # header for the service provider
|   |-- AtomicNumber.cxx                      # source for the service provider
|   `-- atomic_number_standard.fcl          # "standard" service configurations
`-- Services                                    ## art service interface code ##
    |-- AtomicNumberService.h            # header for the art service interface
    `-- AtomicNumberService_service.cc # implementation of art service interface

test/Services/AtomicNumber/                   ### contains the service tests ###
|-- Providers                              ## unit tests for service provider ##
|   |-- AtomicNumber_test.cc         # plain unit test with fixed configuration
|   |-- BoostedAtomicNumber_test.cc     # unit test based on Boost test library
|   |-- ValidateAtomicNumberConfiguration_test.cc   # unit test with validation
|   `-- test_krypton_atomic_number.fcl      # configuration for Boost unit test
`-- Services                           ## unit test for art service interface ##
    |-- AtomicNumberTest_module.cc              # test module using the service
    `-- test_krypton_atomic_number.fcl      # configuration of a test using art
~~~~

Each directory also has its own `CMakeLists.txt` file.

LArSoft mildly recommends the following file name suffices:

* `.h` for all the header files
* `.cc` for modules, services and tests; this is because CET build macros prefer
  the `.cc` suffix
* `.cxx` for algorithm implementation and anything not connected to _art_

If adding code to an existing directory, it's good practise to spend a couple of
minutes to observe the name patterns of files in the directory, its parent and
its siblings.


### Directory structure                                                      ###

The directory structure is overly detailed for such a small project, but it
contains main essential components.

First, the code is divided into two disjoint subtrees that replicate the same
internal structure. This is a LArSoft prescription: all the code and
configuration files are in `larexamples` subdirectory, and the tests are under
the `test` subdirectory.

The choice of two sublevels `Services` and then `AtomicNumber` is driven by
clarity of organisation, and may be too much for your service.
It is conceivable that the same directory hosts more than one service (see e.g.
`lardata/DetectorInfo` and `lardata/DetectorInfoServices`).

Internally, the subdirectory `AtomicNumber` contains two directories.
It is important that the art service interfaces, that are art-dependent, are
compiled in separate libraries than the service providers, that have smaller
framework dependency. The simplest way to achieve this is to have the two sets
in two different directories, as in this example. Alternatively, multiple
libraries can be compiled from sources in a single directory by a careful tuning
of the `CMakeLists.txt` file.



## The service provider: `AtomicNumber`  #######################################

The service provider is where all the action goes.
In this example, there is not much action ongoing though: the provider just
reads a value from the configuration, and it returns it back when asked.

The provider is split in the usual header and implementation file.


### `CMakeLists.txt`                                                         ###

The tasks of this `CMakeLists.txt` file are:

- generate a library for the provider
- install headers and source code (meaning to make sure they appear in the
  final UPS product
- install FHiCL configuration (as above)

The installation part is done by the usual macros (`install_XXX()`).
The generation of the library can happen with either `art_make()` or
`art_make_library()` macros. They both do very similar things in this case,
and they will grab all the source files that end in `.cc`, `.cxx` etc. and that
do not have a "magic" ending (`_module.cc`, `_service.cc`, ...), and pull them
together into a library that will be called after the path it is created from,
which turns into `larexamples_Services_AtomicNumber_Providers`.
We recommend that, although inconvenient, the library name is left this long,
since it helps avoiding collisions (`Providers` is not a good library name):

- the library file name is `liblarexamples_Services_AtomicNumber_Providers.so`
  (in Linux) or `.dylib` (in Darwin), in `$LAREXAMPLES_LIB` directory
- the name to be used in `CMakeLists.txt` files including it (as in this service
  below) is `larexamples_Services_AtomicNumber_Providers`
- this name does not appear in the configuration files

In this case, we opted for `art_make()`.
Filling the list of libraries can be tricky.
A way to address the problem is to give a minimalist first try and then add as
needed: the build system settings will tell us loudly if anything is missing.
A recipe that gives good results to have a first list is to:

1. check all the included headers
2. add a library for each of them

Running the following command from
`${MRB_SOURCES}/larexamples/larexamples/Services/AtomicNumber/Providers` :

~~~~    
grep -h -e '# *include' *
~~~~

gives the output:

~~~~
#include "AtomicNumber.h"
#include "art/Utilities/Exception.h"
#include "fhiclcpp/ParameterSet.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/Table.h"
~~~~

The first is the library we are building, so we don't include it.
The second header comes from `art/Utilities`: the library name is contained in
a variable in _cmake_ called `${ART_UTILITIES}`.
The next three describe things in the FHiCL C++ library. Following the pattern,
we would get two libraryes: `${FHICLCPP}` and `${FHICLCPP_TYPES}`. It turns out,
FHiCL C++ produces only one library with everything, and that is in
`${FHICLCPP}`.
You can peek at the libraries from that UPS product by running

~~~~
ls "$FHICLCPP_LIB"
~~~~

In this case, it worked pretty well. The UPS products where this approach
typically fails are _nutools_ (where the include path does not even tell you
it's a _nutools_ header), ROOT, CLHEP.

Our examples follow a non-standard and not recommended practice: we install
`CMakeLists.txt` files and FHiCL files with `install_source()`. This is done
only because this is an example that should be distributed complete.
Normally, FHiCL files are installed in the correct location thanks to the
`install_fhicl()` directive, and `CMakeLists.txt` files are not installed at
all.


### `AtomicNumber.h`                                                         ###

The design of this service is extremely simple.
We allow it to receive configuration from the framework, and we have just one
information we provide.

#### Documentation explanation

The header is documented with Doxygen.
The complete documentation goes into the header. This is recommended because
headers might be shipped without implementation, and because headers contain
all the declarations that callers may use.

We first document the file itself (at the very beginning) to include author name
and contact information, and a short description of the content of the file.
The date is a _creation_ date and it's not essential.

The namespace should be documented only if unique, that is not the case here.

The provider class should have documentation for the class itself, for every
non-obvious member function, and for _all_ data members.
The class documentation includes a detailed description of the configuration
parameters, that can be much more verbose than the one by `fhicl::Comment`
(see [configuration and validation] below).
Note the use of grouping to collect together methods dealing with the same
topic. In this example its use (the "Accessors" group) is quite specious, since
there is only one method after all. This construct is used for example in
`geo::GeometryCore` documentation to group methods operating with TPCs, with
wire planes, with wires, etc.

#### Namespace

The provider is placed in a namespace that describes its general category.
The namespace `lar` is used for things that are specific of LArSoft mechanics.
Services and algorithms rarely fall in it, as there are more appropriate ones
like `sim` (simulation), `reco` (reconstruction), etc.

#### Configuration and validation

The configuration of the provider relies on FHiCL constructs to document and
validate it at run time. This infrastructure is described in the
[_fhicl-cpp_ wiki][fhiclcpp].
The idea is that the configuration parameters are represented by special data
member within a single data structure. In our example this data structure is
contained in the provider itself and it's called `Config`. All of its one
elements have a "comment" concisely describing their purpose (and normally
the unit their values are expressed in). The link shows how to create more
complex structures than just simple numbers.
The provider constructor directly accepts a class of type `Config`. The only
easy way to construct a `Config` object is via a parameter set. The _art_
framework does that in one way (see [AtomicNumberService.h]), and the tests do
it in another (see [ValidateAtomicNumberConfiguration_test.cc] and the other
`AtomicNumber` constructor): the `Config` constructor is where the two ways
finally merge.
Note that the provider does not run the validation. The test must invoke
validation explicitly, and _art_ framework does the same behind the scenes
when constructing the service.

#### Coding practises

The ridiculously long include guard
`LAREXAMPLES_SERVICES_ATOMICNUMBER_PROVIDER_ATOMICNUMBER_H` is in
fact the recommended one. Having naming collisions for include guards is pretty
much guaranteed to yield misleading compilation errors. So we stick the whole
file path into it. You can learn more about this in the _art_ workbook (appendix
F in version 0.90). We have used an upcase identifier as it's custom to have
C preprocessor definition names, _and only those_, uppercase.

There are two constructors. One is the usual one based on FHiCL `ParameterSet`,
the other is a more unusual one directly based on our configuration class.
The latter one is intended to be used indirectly and it is exposed for the _art_
service and the tests to be able to enable configuration validation (see also
[Configuration and validation] above). The explanation of their existence is
better seen in their use, in [AtomicNumber_test.cc], in
[ValidateAtomicNumberConfiguration_test.cc] and in [AtomicNumberService.h].
Keep in mind that the constructor based on a `ParameterSet` does _not_ use
validation. The other one does not either, but it enables the caller to do
that.

LArSoft recommends that service providers are not copyable nor movable.
Some LArSoft utilities (noticeably, `lar::providerFrom()` function) will refuse
to work otherwise. A set of deleted constructors and assignment operators
fulfils this requirement.

We also insist that the data members be private. This complicates the interface
because of the need of "accessors" (like the `Z()` method here) but improve
maintainability, allowing changes in the underneath representation being
absorbed by the implementation of the interface, that can stay unchanged (for
example, imagine replacing a C array data member with a `std::vector` or
`std::array`).

The choice of a data member name ending with an underscore character (`Z_`) is
not a recommendation, but just one of the possible solutions.
It _is_ recommended that the names for the interface methods have clear meaning,
internally consistent style, and then briefness: e.g., avoid having
`atomic_number()` and `nucleonNumber()` together. Remember that especially for
a service once the names are set the whole community will have to live with
them.


### `AtomicNumber.cxx`                                                       ### 

In this example, the implementation file is completely trivial.
Its mere presence, though, has the effect that a library is generated for
`AtomicNumber`. You will rarely find yourself in a situation where the
implementation file is not necessary, and we suggest that also in such case
you add a trivial one nonetheless.


### `atomic_number_standard.fcl`                                             ### 

With the service provider, it's a good idea to provide also some example
configuration that reflects the most common use case (or cases).
The FHiCL file provided here can be used to configure both the provider and the
art service.
It contains the configurations in a "prolog", that is a special section that
contains pieces of configuration that can be reused in the main configuration.
An example of how is in the test configuration `test_krypton_atomic_number.fcl`
(see below).
It also contains a fair amount of comments, describing what is inside the file
itself. It would also include a list of "dependencies", mainly a list of
services this provider depends on: nothing in this example, but check for other
examples that do have this kind of dependency.

This configuration file must be present in the final UPS product. This is
achieved by the `install_fhicl()` macro in `CMakeLists.txt` in `Providers`
directory.



## The service: `AtomicNumberService`  #########################################

The _art_ service is extremely simple in this example: it does not need to react
to framework state changes (like the opening of a new input file or event), and
it does not implement an abstract interface (that is, there is only one possible
implementation for this service).
The only tasks of this service are:

* manage and provide the service provider, `AtomicNumber`
* implement the (terse) service interface that _art_ requires
* implement the (even terser) interface that LArSoft recommends

It is placed in a separate directory to have dependencies independent from the
ones of the provider (see [Directory structure] above for an explanation).

### AtomicNumberService.h                                                    ###

The header has two main components: the declaration of the service class and
the declaration of the _art_ service macros.

For the first part we use a template that LArSoft providers to create the
simplest _art_ service possible, that can only return its provider.
This template imposes requirements on the provider, that are documented with
the template itself.

The second part is required by _art_, that is in this way informed of the
existence of this class as a service.

The only interesting part here are names: we encourage the _art_ service to live
in the same name as the service provider. Also, we recommend to have the names
of service and provider be easy to match: LArSoft uses often a (meaningful) name
for the provider, and the same name with "Service" appended for the _art_
service. Other times, the provider is appended a "Provider" suffix too; this is
usually to avoid name conflicts with existing classes.

Note that basically no documentation is provided. The provider documents all the
information specific to the service.

### `AtomicNumberService_service.cc`                                         ###

The implementation file is required as it needs to contain the _art_ service
definition macro call. The (already small) implementation of the service class
itself is included in the template itself, and no customisation is required
here.


## Tests  ######################################################################

The purpose of these "unit" tests is to exercise all the features of the service
provider and its _art_ interface.
We have two groups of tests. The first group exercises the provider only, and
it does not depend on the framework. The second one exercises the functions that
are specific to the _art_ service interface, and does not necessarily tests the
features that were tested also by the provider. An even better pattern is to
have a test that can be run in both modes -- one of `geo::GeometryCore` tests
is such: it has a test library and both the provider and the service tests call
it.
The following tests are implemented:

* `AtomicNumber_test`: provider unit test with no configuration
* `BoostedAtomicNumber_test`: provider unit test that uses Boost unit test,
   configured via FHiCL file 
* `ValidateAtomicNumberConfiguration_test`: provider unit test using
  configuration presentation and validation
* `AtomicNumberTest_module`: service unit test

When `mrb test` is used, all the tests are run automatically and all failures
are individually reported. A global output log is also available somewhere,
typically in `${MRB_BUILDDIR}/Testing/Temporary/LastTest.log`.


### CMakeLists.txt                                                           ###

Tests are declared to `cmake` via the `cet_test()` macro.
This macro can compile the test libraries and executable, run the test, verify
the output and report errors. Some of these features are only rarely used.

In case of a stand-alone unit test, it's usually enough specify a test name
(mandatory), source files to be compiled into the test executable, and a list
of libraries to link with it. In our examples we did not specify the source
files, which are therefore guessed by `cet_test()` by adding `.cc` to the test
name: for example, in `AtomicNumber_test`, the source will be expected to be in
`AtomicNumber_test.cc`.
In `BoostedAtomicNumber_test`,we added a command line argument with `TEST_ARGS`
and we also specified that that file needs to be copied in the test directory
with `DATAFILES`. We rely on `cet_test()` to link the proper Boost libraries to
enable unit testing, by `USE_BOOST_UNIT` flag. Note that the double-dash (`--`)
is required by Boost to correctly interpret the arguments as belonging to the
test rather than to the Boost unit test framework. As such, they are needed
only when running a test with Boost.

For the _art_ service test, we run a full `lar` job: we specify that the
executable name is special, `lar`, with `TEST_EXEC`, and we also tell
`cet_test()` that it should not bother to try and build it: it's `HANDBUILT`
already. We add the _lar_ option `--rethrow-all` that should prevent _art_ from
absorbing, dealing with and eventually hiding exceptions: if an exception
occurs and reaches _art_, it will not try to handle it.
The job requires a test module. To build its library we use the usual
`simple_plugin()` macro, that is not specific for testing. It's worth noting
that the this list of libraries is the only one including _art_: the provider
tests do not depend on it.

As mentioned while describing the other `CMakeLists.txt`, we perform here a more
complete installation than it would usually be done for non-example code.


### AtomicNumber_test.cc                                                     ###

This test uses hard-coded configurations. This is an approach complementary to
using user-supplied configurations: it allows to test with total predictability
of results, but it does not necessarily test real use cases.
The `BoostedAtomicNumber_test` test takes the alternative approach.

The general pattern of this test is to have a test function that accepts a
configuration and the expected test results, performs the test and verifies the
results. This function is called here twice, to test the default configuration
and a custom one. The test is a common executable with a `main()` function that
runs the tests and returns an exit code. Failing tests have to return a non-zero
exit code, in the UNIX tradition. We chose here to return, in fact, the number
of errors encountered. Note that exit codes can be 8 bit signed integers, that
don't accommodate for large values.

The actual test function, `TestConfiguration()`, illustrates the use of a
somehow cryptic facility, the `TesterEnvironment` class.
The gain in using it is that it takes care of:

* parsing a FHiCL file (if provided, which we don't here)
* initializing the message facility service
* keeping track of all service configurations (and test algorithm configuration
  too: another facility we don'y use here)

This facility can be extended to set up, manage and provide other service
providers too, which makes it a small test framework in his own. But we don't do
that here either.

The test environment is a template that requires a configuration object.
The configuration object holds information about the configuration: a bunch of
strings representing names of services, configuration file paths, and actual
FHiCL configuration. The test environment is initialised with one of these
objects and will use its information.

We first initialise the configuration object, giving it a test name (mostly eye
candy) and we inform it of which configuration string is associated to a service
called `"AtomicNumberService"`. This is now just a label, but it matches the
label that would be used in a full _art_-aware configuration file.
Then we create a `TesterEnvironment` object with this configuration.
There are many ways to do that; in this example we take the simplest one of
using a function that does just that, given the configuration as first argument.

We create a new service provider `AtomicNumber Zprov` using the constructor that
takes a `fhicl::ParameterSet` as a argument. We obtain the parameter set from
the test environment, asking it about the same label we just set. In the while,
it converted the configuration _string_ we gave it into a _parameter set_.

The test itself is fairly trivial. We call the member function `Z()` and if the
result is unexpected, we write an error message and increase an error count.

In the end, the error count is returned. The `main()` functions will sum all the
error counts and exit with that as the exit code, and the system running the
test will know whether it was successful (exit code 0) or not.


### BoostedAtomicNumber_test.cc                                              ###

This test is similar to `AtomicNumber_test`, differing in two important aspects:

* it requires a configuration file from command line
* it is implemented with Boost unit test suite

The configuration file is required to have a section configuring `AtomicNumber`
provider as it were in a _art_ job, via `AtomicNumberService` parameter set,
and also have the expected results expressed in a`physics.analyzers.expected`
parameter set, in a configuration equivalent to a _art_ job with an analyser
module instance called `expected`. The test expects this parameter set to have
the same structure as the service provider configuration.
Such a FHiCL configuration file is provided: `test_krypton_atomic_number.fcl`.

Note that the requirement on the configuration file are documented at top of
the test source, in the customary Doxygen format.

#### Running a Boost test

A Boost unit test executable supports a large number of options.
Among the most useful: `--report_level=detailed` will give a precise report of
what went well and what went wrong in the test; `--log_level=all` will print all
the checks on screen. For example:
~~~~
"${MRB_BUILDDIR}/larexamples/bin/BoostedAtomicNumber_test" --log_level=all \
  "${MRB_SOURCE}/larexamples/test/Services/AtomicNumber/Providers/test_krypton_atomic_number.fcl"
~~~~

#### Boost unit test library

The Boost unit test suite is made of C preprocessor macros that make the code
look like invalid C++ and make error messages nearly unusable.
It provides a good deal of facilities to automate the most common test tasks and
reduce the amount of typing.
The implementation we use here uses a _fixture_. A fixture is a class that
provides an environment in which the tests run. The tests in the
`BOOST_AUTO_TEST_CASE()` blocks are aware of the content of the fixture. In
fact, they see all the public members of the fixture class directly (they
constitute member functions of a class derived by the fixture class, created
automatically by Boost).
We use our own class `AtomicNumberTextFixture` as a fixture, that has among
its public data members an instance of `AtomicNumber` provider called `Zprov`.
Therefore, our tests in `BOOST_AUTO_TEST_CASE()` will be able to access it
directly, for example writing `auto Z = Zprov.Z();`.

#### The custom fixture class

Our fixture class can be seen as made of two parts:

1. general test environment including configuration handling
2. an instance of our provider

The fixture class _derives_ from a test environment, that is very similar to
`TesterEnvironment` class used in `AtomicNumber_test`. The difference is that
the configuration object is not `testing::BasicEnvironmentConfiguration`, but
a class derived from it, `testing::BoostCommandLineConfiguration`, that adds
the ability of automatically read the configuration file from command line.
Here tricks are needed because we don't create the fixture object explicitly,
but rather have Boost take care of that. Boost will use the default constructor,
so we must be sure that our fixture constructs exactly as we want on the spot,
since after the construction e are not given a chance to fix, tune or adjust it.
The `testing::BasicEnvironmentConfiguration` and `testing::TesterEnvironment`
classes take care of all those tricks. Still we need additional data members
(for example, we need an instance of the service provider `AtomicNumber`),
so we have to derive our fixture from `testing::TesterEnvironment` instead of
using it directly.

The instance of service provider is held as data member, and initialised in the
default constructor in the same way as in `AtomicNumber_test`, calling the
constructor with a parameter set. Here the parameter set is obtained by the
fixture class itself, that derives from `testing::TesterEnvironment`.

We also save the set of values describing the expected results, that comes from
the configuration file with the label `"expected"`. `TesterParameters()` method
assumes that there are test analyser modules, configured in `physics.analyzers`
as per _art_ rules.

#### The test cases

The test starts with the declaration of which fixture class we use, and a name
for the test: `BOOST_FIXTURE_TEST_SUITE()`. This is matched by the declaration
that the test is over: `BOOST_AUTO_TEST_SUITE_END()`. You can imagine the call
`BOOST_FIXTURE_TEST_SUITE(BoostedAtomicNumberTest, AtomicNumberTestFixture)`
to be equivalent to a line
`class BoostedAtomicNumberTest: public AtomicNumberTestFixture {`, and the
closing `BOOST_AUTO_TEST_SUITE_END()` equivalent to a `};`: everything in
between these belongs to the `BoostedAtomicNumberTest` test class. The test case
`BOOST_AUTO_TEST_CASE(AllTests)` macro call might be method definitions, like
`void AllTests()`.
Boost unit test suite will know what to do with this class and its methods.

The only test case we have performs the same test as `AtomicNumber_test`.
First, we extract from `physics.analyzers.expected.Z` the value we expect for Z,
and then we verify that `AtomicNumber::Z()` returns that very same value.
To do that we use a `BOOST_CHECK_EQUAL()` macro that will take care of
communicating errors in a way that depends on the test arguments.


### ValidateAtomicNumberConfiguration_test.cc                                ###

This test just checks that the given service configuration is valid.
It relies on the validation feature of FHiCL library and on the fact that the
provider supports configuration via objects based on `fhicl::Atom`,
`fhicl::Table` and the such (`AtomicNumber::Config`).

As usual, the instructions for running the test are described in words in the
documentation of the source file.

The test is made of three part: configuration of the test environment, printing
the allowed provider configuration on screen, and checking the provider
configuration from the file specified on the command line.

#### Testing environment

The test environment here is similar to the one in `AtomicNumber_test`, with two
differences.

The first difference is that the configuration file path is read from the
command line. The configuration object is created with knowledge of the command
line arguments (`argc` and `argv`), which it will use to extract the path.

The second difference is that we don't provide a default configuration. We don't
need to, since we expect the configuration from command line. But this means
that if no configuration file is specified, we do not have any fallback
configuration and the test will immediately fail.

#### Printing the allowed configuration

An object of type `fhicl::Table` is able to print the configuration it
represents. All we have to do is to create such a table with provider's `Config`
as content. Such an object is useful enough that `AtomicNumber` provider has a
name for it, `parameters_type`. A technical detail is that to create such a
table we need to give either a parameter set or a name. Neither of them is
important, so we choose the fastest way, just provide a name.
Then it's only matter of calling its `print_allowed_configuration()` method.

#### Testing the validity of the configuration

The other thing an object of type `fhicl::Table` can do is to validate a FHiCL
parameter set. We provide this method a parameter set and a list of keys that
should be ignored, and the method `validate_ParameterSet()` checks that:

* all the elements of the wrapped `Config` object that have no default value
  are present in the specified parameter set
* that no key in the parameter set is present that does not match any element in
  the wrapped `Config` object, with the possible exception of the ignored keys

If any of these checks fails, an exception is thrown.
In the test, we have asked to ignore a key called `"service_type"`. This key is
by default added by _art_ and some configuration files end up having it (for
example, configuration files derived from the dump of a _art_-processed
configuration, as with `config_dumper` or the `--debug-config` option of `art`).
With this, any valid _art_ configuration file including the service
`AtomicNumberService` is expected to pass this test.


### AtomicNumberTest_module.cc                                               ###

A test for an _art_ service requires running `lar` with the proper configuration
file, possibly including one or more test modules.

The configuration file, called `test_krypton_atomic_number.fcl`, that is in fact
based on its namesake in the `Providers` test directory, but dressed to work
with _art_: it adds a test module `"atomicnumbertest"` of type
`AtomicNumberTest`.

In this example, the _art_ service does not add any functionality on top of the
provider, so only the trivial test `AtomicNumberTest` is provided. It obtains
the service provider from the framework (testing that `lar::providerFrom()`
works with our service), and exercises the provider one-method interface.
The test is performed in the `beginJob()` method: at that time, services are
already available but no input file is open. In this way, no input file is
actually needed for the test to run --- and in fact we don't provide any.

The validation of the configuration, that for the provider was explicitly
checked only in `ValidateAtomicNumberConfiguration_test`, is automatically
performed by _art_, both in this test and every time the service is instantiated
in a regular run.


## Questions?  #################################################################

If you have any question about the example, please contact its author.
This section will be populated with questions and their answers.


Version 1.11: August 15, 2017 (seligman@nevis.columbia.edu)
  Teeny	change: filename README -> README.md since this is a Markdown file.


[LArSoft wiki]:
  <https://cdcvs.fnal.gov/redmine/projects/larsoft/wiki/Writing_LArSoft_algorithms>
[fhiclcpp]:
  <https://cdcvs.fnal.gov/redmine/projects/fhicl-cpp/wiki/Configuration_validation_and_fhiclcpp_types>
