#ifndef RESOLUTION_H_INCLUDED
#define RESOLUTION_H_INCLUDED

/***
*Resolution definerar spelarfönstrets maximala storlek
*Korten som delas ut beror också på desssa konstanter då de centreras med dessa.
*
***/
#define RES_X 640  //spelarplanets höjd
#define RES_Y 480   //spelarplanets bredd

/***
*Upplösningen på spelkorten, får ENDAST ändras om spelkorten i CARD.png ändras
*
***/
#define HEIGHT 105  //kortets höjd
#define WIDTH 70    //kortets bredd

/***
*storleken på dropzone i mitten
*
***/

#define DROP_X 300
#define DROP_Y 200

#endif // RESOLUTION_H_INCLUDED
