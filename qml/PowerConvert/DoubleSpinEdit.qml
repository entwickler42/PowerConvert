import QtQuick 1.0

Item{
    id: item
	property alias label: label.text
	property alias text: textEditValue.text		
	
	signal accepted();
	
	height: 32
	width: 160
	
	Column{
		spacing: 3
		
		Text {
			id: label
			x: 12
			font.pointSize: 4			
			font.italic: true
			font.bold: true	
			smooth: true					
		}	
		
		Rectangle{			
			radius: 15
			opacity: 0.75
			color: "white"
			border.color: "#000000"			
			
			width: item.width
			height: item.height			
			
			TextInput{				
				id: textEditValue
				anchors.fill: parent
				anchors.topMargin: 2
				horizontalAlignment: "AlignHCenter"			
				font.pixelSize: (parent.height - 4)* 0.80 
				font.italic: true
				font.bold: true
				smooth: true
				validator: DoubleValidator {}				
				onAccepted: item.accepted()
				onTextChanged: item.accepted()
			}
		}		
	}
}

