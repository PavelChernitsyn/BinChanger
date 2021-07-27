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
        function onBit_strChanged() {label_bit_str.text = bit_changer.bit_str}
        function onHex_strChanged() {input.text = bit_changer.hex_str}
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
                text: "0"
                implicitWidth: 200
                validator: RegExpValidator {
                    regExp: /[A-F0-9]{2}/
                }
                onTextChanged: bit_changer.set_number(input.text)
            }
        }

        //Output
        RowLayout {
            Label {
                id: label_bit_str
                font.pixelSize: 50
                text: bit_changer.bit_str
            }
        }

        RowLayout {
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
        }
        onRejected: {}
    }
}
