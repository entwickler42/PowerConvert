import QtQuick 1.0
import EmathListModel 1.0

Rectangle {    
    width: 640
    height: 340	
	
	Image {
		id: imageBackground
		anchors.fill: parent
		source: "Image/background.png"
	}
	
	Row{
		id: inputRow
		y: 35
		spacing: 20			
		anchors.horizontalCenter: parent.horizontalCenter		
		
		DoubleSpinEdit{
			label: "Value in dBm"
			text: listModel.value
			onAccepted: listModel.value = text;	
		}		
		DoubleSpinEdit{
			label: "Gain in dBm"
			text: listModel.gain
			onAccepted: listModel.gain = text;
		}
		DoubleSpinEdit{
			label: "Frequency in MHz"
			text: listModel.frequency
			onAccepted: listModel.frequency = text;
		}	
	}
	
	Rectangle {
		x: inputRow.x
		y: 100
		width: inputRow.width
		height: 200
		opacity: 0.8
		border.color: "#000000"
		radius: 15
		
		ListView {						
			id: resultList			
			model: listModel			
			anchors.fill: parent	
			anchors.margins: 10, 10, 10, 10
			spacing: 5
			clip: true			

			delegate: Row{
				spacing: 5
				Rectangle{
					width:  100
					height: 30		
					radius: 15					
					Text { text: UnitName; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
				}
				Rectangle{
					width:  resultList.width - 100
					height: 30
					radius: 15
					anchors.leftMargin: 10;
					Text { text: UnitValue; anchors.horizontalCenter: parent.horizontalCenter }
				}					
			}
		}
	}
	
	MouseArea{
		x: 594
		y: 8
		width: 40
		height: 40
		anchors.rightMargin: 6
		anchors.topMargin: 8
		anchors.bottomMargin: 312
		anchors.leftMargin: 594
		opacity: 1
		visible: true
		clip: false
		anchors.fill: parent
		onClicked: Qt.quit()
	}
}
