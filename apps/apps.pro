TEMPLATE = subdirs

android {
    message("Building android version")
    CONFIG -= generic
    SUBDIRS += android
}

!android {
    message("Building generic version")
    SUBDIRS += generic    
}


