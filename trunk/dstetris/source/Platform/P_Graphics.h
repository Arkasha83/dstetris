#pragma once

#include <nds.h>

enum BUFFER_TYPE
{
    MAIN,
    SUB,
};

//members
u16* P_Graphics_mainBuffer;
u16* P_Graphics_subBuffer;
int P_Graphics_mainW;
int P_Graphics_mainH;
int P_Graphics_subW;
int P_Graphics_subH;

void P_Graphics_assignBuffer(enum BUFFER_TYPE bT, u16* buffer, int w, int h)
{
    switch(bT)
    {
        case MAIN: P_Graphics_mainBuffer = buffer;
            P_Graphics_mainW = w;
            P_Graphics_mainH = h;
            break;
        case SUB: P_Graphics_subBuffer = buffer; 
            P_Graphics_subW = w;
            P_Graphics_subH = h;
            break;
    }
}

void FillRectangle(enum BUFFER_TYPE bT, int top, int bottom, int left, int right, u16 color)
{
	int i,w,h;
	bool mainB = ( bT == MAIN );
    u16* buffer = mainB ? P_Graphics_mainBuffer : P_Graphics_subBuffer;
    w = mainB ? P_Graphics_mainW : P_Graphics_subW;
    h = mainB ? P_Graphics_mainH : P_Graphics_subH;
    
	for(i = top * w; i < bottom * w; i++)
	{
    	if(i%w > left && i%w < right)
		    buffer[i] = color;
	}
}

void DrawHorizontalLine(enum BUFFER_TYPE bT, int x, int x2, int y, u16 color)
{
	int i,w;
	bool mainB = ( bT == MAIN );
    u16* buffer = mainB ? P_Graphics_mainBuffer : P_Graphics_subBuffer;
    w = mainB ? P_Graphics_mainW : P_Graphics_subW;
	for(i = x + (y*w); i <= x2 + (y*w); i++)
	    buffer[i] = color;
	
}
void DrawVerticalLine(enum BUFFER_TYPE bT, int y, int y2, int x, u16 color)
{
	int i,w;
	bool mainB = ( bT == MAIN );
    u16* buffer = mainB ? P_Graphics_mainBuffer : P_Graphics_subBuffer;
    w = mainB ? P_Graphics_mainW : P_Graphics_subW;
	for(i = x + (y*w); i <= y2*w; i+=w)
	    buffer[i] = color;
}

void DrawRectangle(enum BUFFER_TYPE bT, int top, int bottom, int left, int right, u16 color)
{
     DrawHorizontalLine(bT,left,right,top,color);
     DrawHorizontalLine(bT,left,right,bottom,color);
     DrawVerticalLine(bT,top,bottom,left,color);
     DrawVerticalLine(bT,top,bottom,right,color);
}


//see http://www.dev-scene.com/NDS/Tutorials_Day_3#Polygons
void DrawLine(enum BUFFER_TYPE bT, int x1, int y1, int x2, int y2, u16 color)
{
    int w;
	bool mainB = ( bT == MAIN );
    u16* buffer = mainB ? P_Graphics_mainBuffer : P_Graphics_subBuffer;
    w = mainB ? P_Graphics_mainW : P_Graphics_subW;
    int yStep = w;
    int xStep = 1;      
    int xDiff = x2 - x1;
    int yDiff = y2 - y1;
 
    int errorTerm = 0;
    int offset = y1 * w + x1; 
    int i; 
    
    //need to adjust if y1 > y2
    if (yDiff < 0)       
    {                  
       yDiff = -yDiff;   //absolute value
       yStep = -yStep;   //step up instead of down   
    }
    
    //same for x
    if (xDiff < 0) 
    {           
       xDiff = -xDiff;            
       xStep = -xStep;            
    }        
 
    //case for changes more in X than in Y	 
    if (xDiff > yDiff) 
    {                            
       for (i = 0; i < xDiff + 1; i++)
       {                           
          buffer[offset] = color;  
 
          offset += xStep;           
 
          errorTerm += yDiff;     
 
          if (errorTerm > xDiff) 
          {  
             errorTerm -= xDiff;     
             offset += yStep;        
          }
       }
    }//end if xdiff > ydiff
    //case for changes more in Y than in X
    else 
    {                       
       for (i = 0; i < yDiff + 1; i++) 
       {  
          buffer[offset] = color;  
 
          offset += yStep;           
 
          errorTerm += xDiff;    
 
          if (errorTerm > yDiff) 
          {     
             errorTerm -= yDiff;  
             offset += xStep;     
 
          }
       }
    }
 
}