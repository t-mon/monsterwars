TEMPLATE = subdirs

android {
    message("Building android version")
    CONFIG -= generic
    SUBDIRS += android
}

generic {
    message("Building generic version")
    SUBDIRS += generic    
}


