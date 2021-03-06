######################################
#
# Clean all G4 envs
unsetenv  CLHEP_BASE_DIR
unsetenv  CLHEP_INCLUDE_DIR
unsetenv  CLHEP_LIB
unsetenv  CLHEP_LIB_DIR

unsetenv  G4DEBUG
unsetenv  G4INCLUDE
unsetenv  G4INSTALL

unsetenv  G4LEDATA
unsetenv  G4LEVELGAMMADATA
unsetenv  G4NEUTRONHPDATA
unsetenv  G4RADIOACTIVEDATA
unsetenv  G4ABLADATA
unsetenv  G4REALSURFACEDATA
unsetenv  G4NEUTRONXSDATA
unsetenv  G4PIIDATA

unsetenv  G4LIB
unsetenv  G4LIB_BUILD_G3TOG4
unsetenv  G4LIB_BUILD_SHARED
unsetenv  G4LIB_BUILD_STATIC
unsetenv  G4LIB_BUILD_ZLIB
unsetenv  G4LIB_BUILD_GDML
unsetenv  G4LIB_USE_G3TOG4
unsetenv  G4LIB_USE_GRANULAR
unsetenv  G4LIB_USE_ZLIB

unsetenv  G4SYSTEM

unsetenv  G4UI_NONE
unsetenv  G4UI_BUILD_WIN32_SESSION
unsetenv  G4UI_BUILD_XAW_SESSION
unsetenv  G4UI_BUILD_XM_SESSION
unsetenv  G4UI_USE_TCSH
unsetenv  G4UI_USE_WIN32
unsetenv  G4UI_USE_XAW
unsetenv  G4UI_USE_XM
unsetenv  G4UI_USE_QT

unsetenv  G4VIS_NONE
unsetenv  G4VIS_BUILD_DAWN_DRIVER
unsetenv  G4VIS_BUILD_OIWIN32_DRIVER
unsetenv  G4VIS_BUILD_OIX_DRIVER
unsetenv  G4VIS_BUILD_OPENGLWIN32_DRIVER
unsetenv  G4VIS_BUILD_OPENGLXM_DRIVER
unsetenv  G4VIS_BUILD_OPENGLX_DRIVER
unsetenv  G4VIS_BUILD_RAYTRACERX_DRIVER
unsetenv  G4VIS_BUILD_VRML_DRIVER
unsetenv  G4VIS_BUILD_OPENGLQT_DRIVER

unsetenv  G4VIS_USE_DAWN
unsetenv  G4VIS_USE_OIWIN32
unsetenv  G4VIS_USE_OIX
unsetenv  G4VIS_USE_OPENGLWIN32
unsetenv  G4VIS_USE_OPENGLX
unsetenv  G4VIS_USE_OPENGLXM
unsetenv  G4VIS_USE_RAYTRACERX
unsetenv  G4VIS_USE_VRML
unsetenv  G4VIS_USE_OPENGLQT

######################################
#
# g4system.U
#
#+
setenv G4SYSTEM "Linux-g++"
echo "On this machine the G4SYSTEM=$G4SYSTEM"

#
# g4dirs.U
#
#+
if ( X/home/jason/geant4/geant4.9.4.p01 != X/home/jason/geant4/geant4.9.4.p01 ) then
    setenv G4INSTALL "/home/jason/geant4/geant4.9.4.p01/src/geant4"
    echo "On this machine the G4INSTALL=$G4INSTALL"
else
    setenv G4INSTALL "/home/jason/geant4/geant4.9.4.p01"
    echo "On this machine the G4INSTALL=$G4INSTALL"
endif

#+
if ( Xn != Xn ) then
    if ( X/home/jason/geant4/geant4.9.4.p01 != X/home/jason/geant4/geant4.9.4.p01 ) then
        setenv G4INCLUDE "/home/jason/geant4/geant4.9.4.p01/include/geant4"
    else
        setenv G4INCLUDE "/home/jason/geant4/geant4.9.4.p01/include"
    endif

    echo "On this machine the G4INCLUDE=$G4INCLUDE"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/lib != X ) then
    if ( X/home/jason/geant4/geant4.9.4.p01 != X/home/jason/geant4/geant4.9.4.p01 ) then
        setenv G4LIB "/home/jason/geant4/geant4.9.4.p01/lib/geant4"
    else
        setenv G4LIB "/home/jason/geant4/geant4.9.4.p01/lib"
    endif

    echo "On this machine the G4LIB=$G4LIB"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/PhotonEvaporation2.1 != X ) then
    setenv G4LEVELGAMMADATA "/home/jason/geant4/geant4.9.4.p01/data/PhotonEvaporation2.1"
    echo "On this machine the G4LEVELGAMMADATA=$G4LEVELGAMMADATA"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/RadioactiveDecay3.3 != X ) then
    setenv G4RADIOACTIVEDATA "/home/jason/geant4/geant4.9.4.p01/data/RadioactiveDecay3.3"
    echo "On this machine the G4RADIOACTIVEDATA=$G4RADIOACTIVEDATA"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/G4EMLOW6.19 != X ) then
    setenv G4LEDATA "/home/jason/geant4/geant4.9.4.p01/data/G4EMLOW6.19"
    echo "On this machine the G4LEDATA=$G4LEDATA"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/G4NDL3.14 != X ) then
    setenv G4NEUTRONHPDATA "/home/jason/geant4/geant4.9.4.p01/data/G4NDL3.14"
    echo "On this machine the G4NEUTRONHPDATA=$G4NEUTRONHPDATA"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/G4ABLA3.0 != X ) then
    setenv G4ABLADATA "/home/jason/geant4/geant4.9.4.p01/data/G4ABLA3.0"
    echo "On this machine the G4ABLADATA=$G4ABLADATA"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/RealSurface1.0 != X ) then
    setenv G4REALSURFACEDATA "/home/jason/geant4/geant4.9.4.p01/data/RealSurface1.0"
    echo "On this machine the G4REALSURFACEDATA=$G4REALSURFACEDATA"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/G4NEUTRONXS1.0 != X ) then
    setenv G4NEUTRONXSDATA "/home/jason/geant4/geant4.9.4.p01/data/G4NEUTRONXS1.0"
    echo "On this machine the G4NEUTRONXSDATA=$G4NEUTRONXSDATA"
endif

#+
if ( X/home/jason/geant4/geant4.9.4.p01/data/G4PII1.2 != X ) then
    setenv G4PIIDATA "/home/jason/geant4/geant4.9.4.p01/data/G4PII1.2"
    echo "On this machine the G4PIIDATA=$G4PIIDATA"
endif



#
# g4clhep.U
#
if ( X/home/jason/CLHEP != X ) then
    setenv CLHEP_BASE_DIR "/home/jason/CLHEP"
    echo "On this machine the CLHEP_BASE_DIR=$CLHEP_BASE_DIR"
endif

#+
if ( X/home/jason/CLHEP/include != X ) then
    setenv CLHEP_INCLUDE_DIR "/home/jason/CLHEP/include"
    echo "On this machine the CLHEP_INCLUDE_DIR=$CLHEP_INCLUDE_DIR"
endif

#+
if ( X/home/jason/CLHEP/lib != X ) then
    setenv CLHEP_LIB_DIR "/home/jason/CLHEP/lib"
    echo "On this machine the CLHEP_LIB_DIR=$CLHEP_LIB_DIR"
endif

#+
if ( XCLHEP != X ) then
    setenv CLHEP_LIB "CLHEP"
    echo "On this machine the CLHEP_LIB=$CLHEP_LIB"
endif

#+
#
# g4debug
#
if ( Xn == Xy ) then
    setenv G4DEBUG 1
    echo "On this machine the G4DEBUG=$G4DEBUG"
endif


#
# g4ui
#
#+
if ( Xn == Xy ) then
    setenv G4UI_NONE 1
    echo "On this machine G4UI_NONE is set, so no user interfaces are available"
endif

# Check for Windows!
if ( "X$G4SYSTEM" != "XWIN32-VC" && "X$G4SYSTEM" != "XWIN32-VC7" ) then
    if ( Xn != Xy ) then
        setenv G4UI_USE_TCSH 1
        echo "On this machine the G4UI_USE_TCSH=$G4UI_USE_TCSH"
    endif
endif

#+
if ( Xn == Xy ) then
    setenv G4UI_BUILD_XAW_SESSION 1
    echo "On this machine the G4UI_BUILD_XAW_SESSION=$G4UI_BUILD_XAW_SESSION"
endif

#+
if ( Xn == Xy ) then
    setenv G4UI_USE_XAW 1
    echo "On this machine the G4UI_USE_XAW=$G4UI_USE_XAW"
endif

#+
if ( Xn == Xy ) then
    setenv G4UI_BUILD_XM_SESSION 1
    echo "On this machine the G4UI_BUILD_XM_SESSION=$G4UI_BUILD_XM_SESSION"
endif

#+
if ( Xn == Xy ) then
    setenv G4UI_USE_XM 1
    echo "On this machine the G4UI_USE_XM=$G4UI_USE_XM"
endif

#+
if ( Xn == Xy ) then
    setenv G4UI_BUILD_WIN32_SESSION 1
    echo "On this machine the G4UI_BUILD_WIN32_SESSION=$G4UI_BUILD_WIN32_SESSION"
endif

#+
if ( Xn == Xy ) then
    setenv G4UI_USE_WIN32 1
    echo "On this machine the G4UI_USE_WIN32=$G4UI_USE_WIN32"
endif

#+
if ( Xn == Xy ) then
    setenv G4UI_BUILD_QT_SESSION 1
    echo "On this machine the G4UI_BUILD_QT_SESSION=$G4UI_BUILD_QT_SESSION"
endif 

#+
if ( Xn == Xy ) then
    setenv G4UI_USE_QT 1
    echo "On this machine the G4UI_USE_QT=$G4UI_USE_QT"
endif 



#
# g4vis
#
#+
if ( Xn == Xy ) then
    setenv G4VIS_NONE 1
    echo "On this machine G4VIS_NONE is set, so no vis drivers are available"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_BUILD_DAWN_DRIVER 1
    echo "On this machine the G4VIS_BUILD_DAWN_DRIVER=$G4VIS_BUILD_DAWN_DRIVER"
endif

#+
if ( Xy == Xy ) then
    setenv G4VIS_BUILD_OPENGLX_DRIVER 1
    echo "On this machine the G4VIS_BUILD_OPENGLX_DRIVER=$G4VIS_BUILD_OPENGLX_DRIVER"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_BUILD_OPENGLXM_DRIVER 1
    echo "On this machine the G4VIS_BUILD_OPENGLXM_DRIVER=$G4VIS_BUILD_OPENGLXM_DRIVER"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_BUILD_OPENGLWIN32_DRIVER 1
    echo "On this machine the G4VIS_BUILD_OPENGLWIN32_DRIVER=$G4VIS_BUILD_OPENGLWIN32_DRIVER"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_BUILD_OIX_DRIVER 1
    echo "On this machine the G4VIS_BUILD_OIX_DRIVER=$G4VIS_BUILD_OIX_DRIVER"
endif

#+
if ( Xy == Xy ) then
    setenv G4VIS_BUILD_RAYTRACERX_DRIVER 1
    echo "On this machine the G4VIS_BUILD_RAYTRACERX_DRIVER=$G4VIS_BUILD_RAYTRACERX_DRIVER"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_BUILD_OIWIN32_DRIVER 1
    echo "On this machine the G4VIS_BUILD_OIWIN32_DRIVER=$G4VIS_BUILD_OIWIN32_DRIVER"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_BUILD_VRML_DRIVER 1
    echo "On this machine the G4VIS_BUILD_VRML_DRIVER=$G4VIS_BUILD_VRML_DRIVER"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_BUILD_OPENGLQT_DRIVER 1
    echo "On this machine the G4VIS_BUILD_OPENGLQT_DRIVER=$G4VIS_BUILD_OPENGLQT_DRIVER"
endif 


#+
if ( Xn == Xy ) then
    setenv G4VIS_USE_DAWN 1
    echo "On this machine the G4VIS_USE_DAWN=$G4VIS_USE_DAWN"
endif

#+
if ( Xy == Xy ) then
    setenv G4VIS_USE_OPENGLX 1
    echo "On this machine the G4VIS_USE_OPENGLX=$G4VIS_USE_OPENGLX"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_USE_OPENGLXM 1
    echo "On this machine the G4VIS_USE_OPENGLXM=$G4VIS_USE_OPENGLXM"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_USE_OPENGLWIN32 1
    echo "On this machine the G4VIS_USE_OPENGLWIN32=$G4VIS_USE_OPENGLWIN32"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_USE_OIX 1
    echo "On this machine the G4VIS_USE_OIX=$G4VIS_USE_OIX"
endif

#+
if ( Xy == Xy ) then
    setenv G4VIS_USE_RAYTRACERX 1
    echo "On this machine the G4VIS_USE_RAYTRACERX=$G4VIS_USE_RAYTRACERX"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_USE_OIWIN32 1
    echo "On this machine the G4VIS_USE_OIWIN32=$G4VIS_USE_OIWIN32"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_USE_VRML 1
    echo "On this machine the G4VIS_USE_VRML=$G4VIS_USE_VRML"
endif

#+
if ( Xn == Xy ) then
    setenv G4VIS_USE_OPENGLQT 1
    echo "On this machine the G4VIS_USE_OPENGLQT=$G4VIS_USE_OPENGLQT"
endif

#+
if ( X != X )  then
    setenv OGLHOME ""
    echo "On this machine the OGLHOME=$OGLHOME"
endif 

#+
if ( X != X )  then
    setenv OIVHOME ""
    echo "On this machine the OIVHOME=$OIVHOME"
endif 


#+
if ( Xn != X )  then
    setenv XMFLAGS ""
    echo "On this machine the XMFLAGS=$XMFLAGS"
endif 

#+
if ( Xn != X )  then
    setenv XMLIBS ""
    echo "On this machine the XMLIBS=$XMLIBS"
endif 

#+
if ( Xn != X )  then
    setenv XMFLAGS ""
    echo "On this machine the XMFLAGS=$XMFLAGS"
endif 

#+
if ( Xn != X )  then
    setenv XMLIBS ""
    echo "On this machine the XMLIBS=$XMLIBS"
endif 

#+
if ( Xn != X )  then
    setenv XAWFLAGS ""
    echo "On this machine the XAWFLAGS=$XAWFLAGS"
endif 

#+
if ( Xn != X )  then
setenv XAWLIBS ""
echo "On this machine the XAWLIBS=$XAWLIBS"
endif 


#
# Qt Flags and Libs, messy, but needed for backward compatibility
#+
if ( "Xn" == "Xy" || "Xn" == "Xy" )  then
    setenv QTFLAGS ""
    setenv QTLIBS ""
    setenv QTMOC ""
endif

if ( "Xn" == "Xy" || "Xn" == "Xy" )  then
    if ( "X$QTFLAGS" == "X" )  then
        setenv QTFLAGS " "
    else
        setenv QTFLAGS "$QTFLAGS "
    endif

    if ( "X$QTMOC" == "X" )  then
        setenv QTMOC ""
    endif

    setenv GLQTLIBS " "
endif


#
# Because the setting of flags is messy, we separate out the reporting
#
if ( $?QTMOC ) then
    echo "On this machine the QTMOC=$QTMOC"
    echo "On this machine the QTFLAGS=$QTFLAGS"
    # {GL}QTLIBS dependent on what modules were chosen...
    if ( $?QTLIBS )  then
        echo "On this machine the QTLIBS=$QTLIBS"
    endif
    if ( $?GLQTLIBS )  then
        echo "On this machine the GLQTLIBS=$GLQTLIBS"
    endif
endif




#
# Use GDML module
#
#+
if ( Xn == Xy ) then
    setenv G4LIB_BUILD_GDML 1
    echo "On this machine the G4LIB_BUILD_GDML=$G4LIB_BUILD_GDML"
endif 

if ( Xn == Xy ) then
    setenv XERCESCROOT ""
    echo "On this machine the XERCESCROOT=$XERCESCROOT"
endif




#
# Use G3TOG4 module
#
#+
if ( Xn == Xy )  then
    setenv G4LIB_BUILD_G3TOG4 1
    echo "On this machine the G4LIB_BUILD_G3TOG4=$G4LIB_BUILD_G3TOG4"
endif 

if ( Xn == Xy )  then
    setenv G4LIB_USE_G3TOG4 1
    echo "On this machine the G4LIB_USE_G3TOG4=$G4LIB_USE_G3TOG4"
endif 


#
# Use ZLIB module
#
#+
if ( Xn == Xy )  then
    setenv G4LIB_BUILD_ZLIB 1
    echo "On this machine the G4LIB_BUILD_ZLIB=$G4LIB_BUILD_ZLIB"
endif 

if ( X == Xy )  then
    setenv G4LIB_USE_ZLIB 1
    echo "On this machine the G4LIB_USE_ZLIB=$G4LIB_USE_ZLIB"
endif 

#+
#
# g4shared
#
if ( Xy == Xy ) then
    setenv G4LIB_BUILD_SHARED 1
    echo "On this machine the G4LIB_BUILD_SHARED=$G4LIB_BUILD_SHARED"
endif

if ( Xn == Xy ) then
    setenv G4LIB_BUILD_STATIC 1
    echo "On this machine the G4LIB_BUILD_STATIC=$G4LIB_BUILD_STATIC"
endif

#+
#
# g4granular
#
if ( Xn == Xy ) then
    setenv G4LIB_USE_GRANULAR 1
    echo "On this machine the G4LIB_USE_GRANULAR=$G4LIB_USE_GRANULAR"
endif

#####################################################################



#+
#
# G4WORKDIR
#
if ( ${?G4WORKDIR} ) then
    echo "In your environment you have the G4WORKDIR=$G4WORKDIR"
else
    # Check for Windows!
    if ( "X$G4SYSTEM" == "XWIN32-VC" || "X$G4SYSTEM" == "XWIN32-VC7" ) then
        echo "G4WORKDIR will be set to c:/geant4 (in "native" Windows syntax)."
        setenv G4WORKDIR "c:/geant4"
    else # if Unix
        echo "G4WORKDIR will be set to HOME/geant4=$HOME/geant4"
        setenv G4WORKDIR $HOME/geant4
    endif
endif

#
# *NIX Shared Libraries
# If we built Geant4 with shared libraries, we need to add the Gean4
# library directory to (DY)LD_LIBRARY_PATH.
# In all cases, external shared library directories should be added to
# (DY)LD_LIBRARY_PATH

if ( "X$G4SYSTEM" != "XDarwin-g++" ) then
    if ( ${?LD_LIBRARY_PATH} ) then
        if ( ${?G4LIB_BUILD_SHARED} ) then
            setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}	
        endif

        setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${CLHEP_LIB_DIR}

        if ( ${?G4LIB_BUILD_GDML} ) then
            setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${XERCESCROOT}/lib
        endif

    else
        if ( ${?G4LIB_BUILD_SHARED} ) then
            setenv LD_LIBRARY_PATH ${G4LIB}/${G4SYSTEM}
            setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${CLHEP_LIB_DIR}
        else
            setenv LD_LIBRARY_PATH ${CLHEP_LIB_DIR}
        endif

        if ( ${?G4LIB_BUILD_GDML} ) then
            setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${XERCESCROOT}/lib
        endif
    endif
else
    #
    # Darwin Shared Libraries
    # we repeat the above logic, but for DYLD_LIBRARY_PATH
    #   
    if ( ${?DYLD_LIBRARY_PATH} ) then
        if ( ${?G4LIB_BUILD_SHARED} ) then
            setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${G4LIB}/${G4SYSTEM}	
        endif

        setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${CLHEP_LIB_DIR}

        if ( ${?G4LIB_BUILD_GDML} ) then
            setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${XERCESCROOT}/lib
        endif
    else
        if ( ${?G4LIB_BUILD_SHARED} ) then
            setenv DYLD_LIBRARY_PATH ${G4LIB}/${G4SYSTEM}
            setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${CLHEP_LIB_DIR}
        else
            setenv DYLD_LIBRARY_PATH ${CLHEP_LIB_DIR}
        endif

        if ( ${?G4LIB_BUILD_GDML} ) then
            setenv DYLD_LIBRARY_PATH ${DYLD_LIBRARY_PATH}:${XERCESCROOT}/lib
        endif
    endif
endif


#
# Warning about LD_LIBRARY_PATH
#
echo ''
if ( ${?G4LIB_BUILD_SHARED} ) then
    if ( "X$G4SYSTEM" == "XDarwin-g++" ) then
        echo 'DYLD_LIBRARY_PATH is set to include CLHEP and Geant4 libraries. '
    else
        echo 'LD_LIBRARY_PATH is set to include CLHEP and Geant4 libraries. '
    endif
else
    if ( "X$G4SYSTEM" == "XDarwin-g++" ) then
        echo 'DYLD_LIBRARY_PATH is set to include CLHEP libraries. '
    else
        echo 'LD_LIBRARY_PATH is set to include CLHEP libraries. '
    endif
endif
echo 'NOTE : you should verify that the correct path for the CLHEP library'
echo ''
echo ${CLHEP_BASE_DIR}/lib
echo ''
echo 'is included in the dynamic library search path ahead of any other'
echo 'installations of CLHEP on your system that may be referenced by this'
echo 'path.'
echo ''

#
# For BIN
#
setenv PATH ${PATH}:${G4WORKDIR}/bin/${G4SYSTEM}

