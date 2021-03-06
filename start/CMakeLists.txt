# Create a library called "" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR}
${GEANT3_INCLUDE_DIR}
${CLHEP_INCLUDE_DIR}
${BASE_INCLUDE_DIRECTORIES} 
${CMAKE_SOURCE_DIR}/field
${CMAKE_SOURCE_DIR}/pnddata
#${CMAKE_SOURCE_DIR}/pnddata/LmbdData
${CMAKE_SOURCE_DIR}/pnddata/SdsData
${CMAKE_SOURCE_DIR}/PndTools/generalTools
${CMAKE_SOURCE_DIR}/passive
${CMAKE_SOURCE_DIR}/sds/SdsMC
${CMAKE_SOURCE_DIR}/sds/SdsTools
${CMAKE_SOURCE_DIR}/sds/SdsDigi
${CMAKE_SOURCE_DIR}/sds/SdsReco
${CMAKE_SOURCE_DIR}/sds/SdsFEModel
${CMAKE_SOURCE_DIR}/sds
${CMAKE_SOURCE_DIR}/trackbase
${CMAKE_SOURCE_DIR}/start
${CMAKE_SOURCE_DIR}/start/startMC
${CMAKE_SOURCE_DIR}/start/startDigi
${CMAKE_SOURCE_DIR}/start/startReco
${CMAKE_SOURCE_DIR}/start/startTools
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${GLPK_LIB_DIR}
)

link_directories( ${LINK_DIRECTORIES})


########################### create libStart ######################################
set(SRCS

startMC/PndStartDetector.cxx
PndStartPoint.cxx
startTools/PndStartContFact.cxx
startDigi/PndStartStripHitProducer.cxx
startDigi/PndStartHitProducerIdeal.cxx
startDigi/PndStartDigiTask.cxx
startDigi/PndStartNoiseProducer.cxx
startTools/PndStartContFact.cxx
)

set(LINKDEF  StartLinkDef.h)
set(LIBRARY_NAME Start)

set(DEPENDENCIES Base GeoBase ParBase PndData generalTools 
Geane  Sds)

GENERATE_LIBRARY()

########################### create libStartReco ##################################
set(SRCS

startReco/PndStartTimeWalkCorrTask.cxx
startReco/PndStartClusterTask.cxx
startReco/PndStartStripClusterTask.cxx
startReco/PndStartIdealRecoTask.cxx

)

set(LINKDEF  StartRecoLinkDef.h)
set(LIBRARY_NAME StartReco)

set(DEPENDENCIES Base GeoBase ParBase PndData generalTools 
Geane  Sds)

GENERATE_LIBRARY()


