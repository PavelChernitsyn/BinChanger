import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import BackEnd 1.0 //написанный пакет

Window {
    id: mainWin
    width: 640
    height: 480
    visible: true
    title: qsTr("Test Ex for DES")

    BitChanger {
        id: bit_changer
    }

    Connections {
        target: bit_changer
        function onBit_strChanged() {label_bit_str.text = bit_changer.get_bin_str_num()}
        function onHex_strChanged() {input.text = bit_changer.get_hex_str_num()}
    }

    ColumnLayout {
        x: 10
        y: 10

        //Input
        RowLayout {
            Label {
                text: "Input:"
            }
            TextField {
                id: input
                text: bit_changer.get_hex_str_num()
                implicitWidth: 200
                validator: RegExpValidator {
                    regExp: /[A-F0-9]{2}/
                }
                onTextChanged: bit_changer.set_number(input.text)
            }
        }

        //Output
        RowLayout {
//            Label {
//                text: "Output:"
//            }
            Label {
                id: label_bit_str
                font.pixelSize: 50
                text: bit_changer.get_bin_str_num()
            }
        }

        RowLayout {
//            Row {
                Repeater {
                    id: repeater
                    model: 8
                    Rectangle {
                        width: 24
                        height: width
                        radius: width/2
                        color: "red"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                color = bit_changer.on_off_bit(index) ? "green" : "red"
                            }
                        }
                    }
                }
//            }
        }

        // Buttons Inverse and SumFromFile
        RowLayout {
            Button {
                text: "Inverse"
                onClicked: bit_changer.inverse()
            }
            Button {
                text: "SumFromFile"
                onClicked: fileDialog.visible = true
            }
        }

        // on/off bits
//        RowLayout {
//            Label {
//                text: "Bit num(0-7):"
//            }

//            TextField {
//                id: bit_num
//                implicitWidth: 50
//                validator: RegExpValidator {
//                    regExp: /[0-7]{1}/
//                }
//            }

//            Button {
//                text: "On"
//                onClicked: bit_changer.on_bit(bit_num.text)
//            }
//            Button {
//                text: "Off"
//                onClicked: bit_changer.off_bit(bit_num.text)
//            }
//        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "Txt files (*.txt)", "All files (*)" ]
        onAccepted: {
            bit_changer.sum_from_file(fileUrl.toString().replace("file://", ""));
//            console.log("You chose: " + fileUrl.toString().replace("file://", ""))
        }
        onRejected: {
//            console.log("Canceled")
        }
    }
}
