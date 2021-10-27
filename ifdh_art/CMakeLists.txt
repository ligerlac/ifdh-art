
macro( install_ifdh_headers   )
  set(header_install_dir ${${CETMODULES_CURRENT_PROJECT_NAME}_INCLUDE_DIR} )
  message( STATUS "install_ifdh_headers: headers will be installed in ${header_install_dir}" )
  FILE(GLOB headers [^.]*.h [^.]*.hh [^.]*.icc )
  if( headers )
    message( STATUS "installing headers ${headers} in ${header_install_dir}")
    INSTALL( FILES ${headers}
             DESTINATION ${header_install_dir} )
  endif( headers )
endmacro( install_ifdh_headers )


# source
subdirs (IFDHService)
subdirs (IFBeamService)
subdirs (nucondbService)
subdirs (IFFileTransfer)
subdirs (IFCatalogInterface)
subdirs (bin)

