set(LetterClustering_SRCS
	DBScan.cpp
	LetterClustering.cpp
	main.cpp
)

qt4_automoc(${LetterClustering_SRCS})
add_executable(LetterClustering ${LetterClustering_SRCS})
target_link_libraries(LetterClustering ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})