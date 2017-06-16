import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    property string cookie
    RowLayout {
        id: request
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.top: parent.top

        TextField {
            id: requestText
            text: qsTr("https://jira.autodesk.com/rest/api/2/issue/SMOK-40053")
        }
        Button {
            text: qsTr("Send Request")
            onClicked: {
                var xmlHttp = new XMLHttpRequest();
                xmlHttp.onreadystatechange = function() {
                    if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
                        response.text = xmlHttp.responseText
                    }
                }
                xmlHttp.open("GET", requestText.text, true); // true for asynchronous
                xmlHttp.setRequestHeader("Content-type", "application/json");
                xmlHttp.setRequestHeader("cookie", cookie);
                xmlHttp.send();
            }
        }
    }
    Text {
        id : response
    }
}
