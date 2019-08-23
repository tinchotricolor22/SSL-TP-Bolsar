cmake_minimum_required(VERSION 3.14)
project(SSL_TP_Bolsar)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/libs/config)
include_directories(src/libs/domain)
include_directories(src/libs/exporter)
include_directories(src/libs/data)
include_directories(src/libs/parser)
include_directories(src/libs/preferences)
include_directories(src/libs/filter)
include_directories(src/libs/formatter)
include_directories(src/libs/logging)
include_directories(src/libs/processor)
include_directories(src/libs/ui)
include_directories(src/libs/utils)
include_directories(output)

add_executable(SSL_TP_Bolsar
        src/libs/config/config.c
        src/libs/config/config.h
        src/libs/domain/leader.h
        src/libs/exporter/exporter.c
        src/libs/exporter/exporter.h
        src/libs/exporter/exporter_csv.c
        src/libs/exporter/exporter_html.c
        src/libs/exporter/exporter_stdout.c
        src/libs/exporter/exportertypes.h
        src/libs/data/data.c
        src/libs/data/data.h
        src/libs/data/dataonline.c
        src/libs/data/datafile.c
        src/libs/parser/parser.c
        src/libs/parser/parser.h
        src/libs/parser/parserhtml.c
        src/libs/preferences/preferences.h
        src/libs/preferences/preferences.c
        src/libs/filter/filter.h
        src/libs/filter/filterleader.c
        src/libs/formatter/formatter.h
        src/libs/formatter/formatterleader.c
        src/libs/logging/logging.c
        src/libs/logging/logging.h
        src/libs/processor/processor.c
        src/libs/processor/processor.h
        src/libs/processor/processortypes.h
        src/libs/ui/ui.c
        src/libs/ui/ui.h
        src/libs/utils/commons.c
        src/libs/utils/commons.h
        src/main.c)

configure_file(resources/lideres_bcba.html resources/lideres_bcba.html)
configure_file(resources/config.properties resources/config.properties)