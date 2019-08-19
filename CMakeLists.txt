cmake_minimum_required(VERSION 3.14)
project(SSL_TP_Bolsar)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/lib/config)
include_directories(src/lib/domain)
include_directories(src/lib/exporter)
include_directories(src/lib/data)
include_directories(src/lib/parser)
//include_directories(src/lib/preferences)
include_directories(src/lib/filter)
include_directories(src/lib/formatter)
include_directories(src/lib/logging)
include_directories(src/lib/processor)
include_directories(src/lib/ui)
include_directories(src/lib/utils)
include_directories(src/output)

add_executable(SSL_TP_Bolsar
        src/lib/config/config.c
        src/lib/config/config.h
        src/lib/domain/leader.h
        src/lib/exporter/exporter.c
        src/lib/exporter/exporter.h
        src/lib/exporter/exporter_csv.c
        src/lib/exporter/exporter_html.c
        src/lib/exporter/exporter_stdout.c
        src/lib/exporter/exportertypes.h
        src/lib/data/data.c
        src/lib/data/data.h
        src/lib/data/datatypes.h
        src/lib/data/dataonline.c
        src/lib/data/datafile.c
        src/lib/parser/parser.c
        src/lib/parser/parser.h
        src/lib/parser/parserhtml.c
        src/lib/parser/parsertypes.h
        src/lib/preferences/preferences.h
        src/lib/preferences/preferences.c
        src/lib/filter/filter.h
        src/lib/filter/filterleader.c
        src/lib/formatter/formatter.h
        src/lib/formatter/formatterhtml.c
        src/lib/formatter/formattertypes.h
        src/lib/logging/logging.c
        src/lib/logging/logging.h
        src/lib/processor/processor.c
        src/lib/processor/processor.h
        src/lib/processor/processortypes.h
        src/lib/ui/ui.c
        src/lib/ui/ui.h
        src/lib/utils/commons.c
        src/lib/utils/commons.h
        src/main.c)

configure_file(src/resources/lideres_bcba.html src/resources/lideres_bcba.html)