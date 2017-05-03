
mac {
    # libs
    libs.path = Contents/Frameworks
    libs.files = $${MARKDOWN_EDITOR_LIBS}
    QMAKE_BUNDLE_DATA += libs
} else:win32 {
    # libs
    POST_TARGETDEPS += $${MARKDOWN_EDITOR_LIBS}

    DST = $$OUT_PWD/$${DEBUG_MODE}
    DST ~= s,/,\\,g
    for(l,MARKDOWN_EDITOR_LIBS) {
        SRC = $${l}
        SRC ~= s,/,\\,g
        QMAKE_POST_LINK += $$quote(cmd /c xcopy /y /i $${SRC} $${DST}$$escape_expand(\n\t))
    }
} else {
    # libs
    POST_TARGETDEPS += $${MARKDOWN_EDITOR_LIBS}

    for(l,MARKDOWN_EDITOR_LIBS) {
        QMAKE_POST_LINK += cp -Lf $${l} $$OUT_PWD/ ;
    }
}
