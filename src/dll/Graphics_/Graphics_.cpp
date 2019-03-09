// graphics_.cpp : Defines the entry point for the DLL application.
//

#include "..\..\Common\H\wndws.h"
#include "Graphics_.h"
#include "math.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved)
{
    return TRUE;
}
BOOL InitRC(HWND hWnd1, //panel
            void *&hdc, //DC of panel 
            void *&hrc) //rc
{
       HDC *hdc1;       
       HGLRC *hrc1;

       hdc1 = new HDC;
       hrc1 = new HGLRC;

       hdc = (void*)hdc1;
       hrc = (void*)hrc1;

       *hdc1 = GetDC(hWnd1);
       if (!bSetupPixelFormat(*hdc1))
                 return FALSE;

       *hrc1 = wglCreateContext(*hdc1);
       if (!wglMakeCurrent(*hdc1, *hrc1))
       {
            MessageBox(hWnd1,"Error!!!!!!!", "1212",MB_OK);
       }
       RECT rect;
       GetClientRect(hWnd1, &rect);
       int Width = -rect.right+rect.left, Height = rect.top-rect.bottom;

       glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Clean a scene (default blank screen ) 

       //glClearDepth(1.0);                      // Allow clearing the buffer of the depth
      // glDepthFunc(GL_LESS);                   // Type of the test of the depth
       glEnable(GL_DEPTH_TEST);                // allow test of the depth
       glShadeModel(GL_SMOOTH);        // allow fluent color smoothing
       glMatrixMode(GL_PROJECTION);    // Choice of the matrix to projections
       glLoadIdentity();               // Reset of the matrix of projections
       gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
                                // Calculate correlation of the geometric sizes for window
       glMatrixMode(GL_MODELVIEW);     // Choice of the matrix of the viewing to models
      // ReleaseDC(hWnd1, *hdc1);
       return TRUE;//end without errors in initialization
}

void DestroyRC(HWND hWnd, void *&hdc, void *&hrc)
{
    HDC *hdc1 = (HDC*)(hdc);
    HGLRC *hrc1 = (HGLRC*)(hrc);

    wglMakeCurrent(*hdc1,NULL);
    wglDeleteContext(*hrc1);
    ReleaseDC(hWnd,*hdc1);
    delete hdc1;
    delete hrc1;
}

void Resize(HWND hWnd1, //panel
            void *&hdc, //DC of panel 
            void *&hrc) //rc
{
       HDC *hdc1 = (HDC*)hdc;
       HGLRC *hrc1 = (HGLRC*) hrc;

       if (!wglMakeCurrent(*hdc1, *hrc1))
       {
            MessageBox(hWnd1,"Error!!!!!!!", "1212",MB_OK);
       }    
       RECT rect;
       GetClientRect(hWnd1, &rect);
       int Width = -rect.right+rect.left, Height = rect.top-rect.bottom;
       if (Height==0)          // error of division on 0
       {
           Height=5;
       }

       glViewport(0, 0, Width, Height);
               //Reset of the current area of the conclusion and perspective transformations

       glMatrixMode(GL_PROJECTION);            // Choice of the matrix of projection
       glLoadIdentity();                       // Reset of the matrix 

       //glOrtho - multiply the current matrix by an orthographic matrix
       //void glOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far ) 
       // gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
       gluPerspective(130.0f,(GLfloat)Width/(GLfloat)Height,50.0f,100.0f);
	   //gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);//!!!????

                //  Calculation of the correlation of the geometric sizes for window
      glMatrixMode(GL_MODELVIEW);     // Choice of the matrix of the viewing to models
     //  ReleaseDC(hWnd1, *hdc1);
}

void DrawLine(HWND hWnd, //window to draw in it
              void *&hDC,
              void *&hRC,
              float k, //function to draw is y=k*x+b
              float b, 
              TPoint *points, //array of points /////- type is TImage
              DWORD count)//number of points
{
    Resize(hWnd, hDC, hRC);

    RECT rect;
    GetClientRect(hWnd, &rect);
    OffsetRect(&rect, - rect.left, - rect.top);//move the co-ordinate beginning point to  the left-top corner of the window
    glViewport(rect.left, rect.top, rect.right, rect.bottom);//cut area to draw in it
    
    float Wx=(float)100.0*rect.right/rect.bottom;//width along Ox of the field
    float Wy=100.0;//width along Oy of the field;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(5);            
    glLoadIdentity();
    glTranslatef(-Wx,-Wy,-60.0f);

    glLineWidth(2); //width of the line
    glBegin(GL_LINES);//draw co-ordinate lines: Ox
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d(0,0); 
        glVertex2d(2*Wx,0); 
    glEnd();  
    glBegin(GL_LINES);//upper part of arrow Ox
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d((2)*Wx-3,1);
        glVertex2d(2*Wx,0); 
    glEnd();        
    glBegin(GL_LINES);//bottom part of arrow Ox
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d((2)*Wx-3,-1);
        glVertex2d(2*Wx,0); 
    glEnd();


    glBegin(GL_LINES);//draw co-ordinate lines: Oy
        glColor3d(0,0,0);    
        glVertex2d(0,0); 
        glVertex2d(0,2*Wy); 
    glEnd();
    glBegin(GL_LINES);//upper part of arrow Oy
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d(1,(2)*Wy-3);
        glVertex2d(0,2*Wy); 
    glEnd();        
    glBegin(GL_LINES);//bottom part of arrow Oy
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d(-1,(2)*Wy-3);
        glVertex2d(0,2*Wy); 
    glEnd();
//search max x and max y;
    double maxX=0.1, maxY=0.1;
    
    for(DWORD i=0;i<count;i++)
    {
        if(maxX<fabs(points[i].X))
        {
            maxX=fabs(points[i].X);
        }
        if(maxY<fabs(points[i].Y))
        {
            maxY=fabs(points[i].Y);
        }
    }
    Wy=(float)(Wx*maxY/maxX);

    Wx*=2;
    Wy*=2;
    //end of search

    glBegin(GL_LINES);//graphic of y=k*x+b;
        glColor3f(1,0,0);
        glVertex2d(0, Wy*b/maxY);
        glVertex2d(Wx*((-b)/k+10000)/maxX, Wy*(10000*k)/maxY);
    glEnd();
    
    //points
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0,0,1);
    for(i=0;i<count;i++)
    {
        glVertex2d(Wx*points[i].X/maxX,Wy*points[i].Y/maxY);
    }
    glEnd();
    glDisable(GL_POINT_SMOOTH);
    //end points
    
    SwapBuffers(*((HDC*)hDC));
};




void DrawPicture(HWND hWnd, void*&hDC, void *&hRC, TImage &picture)
{
    Resize(hWnd, hDC, hRC);
    RECT rect;
    GetClientRect(hWnd, &rect);
    OffsetRect(&rect, - rect.left, - rect.top);   //move the co-ordinate beginning point to  the left-top corner of the window
    glViewport(rect.left, rect.top, rect.right, rect.bottom);   //cut area to draw in it
    
    float Wy=200.0;   //width along Oy of the field;
    float Wx=(float)Wy*rect.right/rect.bottom;  //width along Ox of the field
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-Wx/2,-Wy/2,-60.0f);
    //glTranslatef(-Wx,-Wy,-60.0f);

    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_POINT_SMOOTH);

    if (picture.Width()>100) 
    {
        Wx/=picture.Width();
    }
    else 
    {
        Wx/=100;
    }
    if (picture.Height()>100) 
    {   
        Wy/=picture.Height();
    }
    else 
    {
        Wy/=100;
    }    
    
    if (Wx>Wy) Wx=Wy;
    else Wy=Wx;
    //Wx=(Wx+Wy)/2;
    //Wy=Wx;

    //glPointSize(4*Wx);

    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    for (DWORD X=0; X<picture.Width(); X++)
    {
        for (DWORD Y=0; Y<picture.Height(); Y++)
        {
            if (picture.Pixel(Y,X)!=0)
            {
                glVertex2d(X,Y);//*wx,wy
            }
        }
    }
    glEnd();
 //   SwapBuffers(*((HDC*)hDC)); 
    

//    ReleaseDC(hWnd, *&hDC);
}

void DrawColorPicture(HWND hWnd, void*&hDC, void *&hRC, TColorImage &picture)
{
    Resize(hWnd, hDC, hRC);
    RECT rect;
    GetClientRect(hWnd, &rect);
    OffsetRect(&rect, - rect.left, - rect.top);   //move the co-ordinate beginning point to  the left-top corner of the window
    glViewport(rect.left, rect.top, rect.right, rect.bottom);   //cut area to draw in it
    
    float Wy=200.0;   //width along Oy of the field;
    float Wx=(float)Wy*rect.right/rect.bottom;  //width along Ox of the field
 
    //float owx=Wx,owy=Wy;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-Wx/2,-Wy/2,-60.0f);


    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_POINT_SMOOTH);

    if (picture.Width()>100) 
    {
        Wx/=picture.Width();
    }
    else 
    {
        Wx/=100;
    }
    if (picture.Height()>100) 
    {   
        Wy/=picture.Height();
    }
    else 
    {
        Wy/=100;
    }    
    
    if (Wx>Wy) Wx=Wy;
    else Wy=Wx;
    //Wx=(Wx+Wy)/2;
    //Wy=Wx;
    //glTranslatef(-owx/2.0f,-owy/2.0f,-60.0f*Wx*100);

    //glPointSize(4*Wx);

    glBegin(GL_POINTS);
    for (DWORD X=0; X<picture.Width(); X++)
    {
        for (DWORD Y=0; Y<picture.Height(); Y++)
        {
			glColor3d((BYTE)(picture.Pixel(Y, X) <<24>>24)/256.0,(BYTE)(picture.Pixel(Y, X) <<16>>24)/256.0,(BYTE)(picture.Pixel(Y, X) <<8>>24)/256.0);
            glVertex2d(X,Y);//*wx,wy
        }
    }
    glEnd();
    SwapBuffers(*((HDC*)hDC)); 
    

//    ReleaseDC(hWnd, *&hDC);
}

/*
void DrawWithSquaresPicture(HWND hWnd, void*&hDC, void *&hRC, TImage &picture, CNet *Net)
{
    Resize(hWnd, hDC, hRC);
    RECT rect;
    GetClientRect(hWnd, &rect);
    OffsetRect(&rect, - rect.left, - rect.top);   //move the co-ordinate beginning point to  the left-top corner of the window
    glViewport(rect.left, rect.top, rect.right, rect.bottom);   //cut area to draw in it
    
    float Wy=200.0;   //width along Oy of the field;
    float Wx=(float)Wy*rect.right/rect.bottom;  //width along Ox of the field
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-Wx/2,-Wy/2,-60.0f);
    //glTranslatef(-Wx,-Wy,-60.0f);

    glEnable(GL_POINT_SMOOTH);
    glDisable(GL_POINT_SMOOTH);

    if (picture.Width()>100) 
    {
        Wx/=picture.Width();
    }
    else 
    {
        Wx/=100;
    }
    if (picture.Height()>100) 
    {   
        Wy/=picture.Height();
    }
    else 
    {
        Wy/=100;
    }    
    
    if (Wx>Wy) Wx=Wy;
    else Wy=Wx;
    //Wx=(Wx+Wy)/2;
    //Wy=Wx;

    glPointSize(4*Wx);

    glBegin(GL_POINTS);
        glColor3f(0,0,0);
        for (DWORD X=0; X<picture.Width(); X++)
        {
            for (DWORD Y=0; Y<picture.Height(); Y++)
            {
                if (picture.Pixel(Y,X)!=0)
                {    
                    glVertex2d(Wx*X,Wy*Y);
                }
            }
        }
    glEnd();

    //draw squares above picture
    CListItem *CR = Net->Current;
    CListItem *CS;
    if (CR!=NULL)
    {
        CS = ((CRow*)Net->Current)->Current;
    }
    Net->Current = Net->First;
    if (Net->Current==NULL)
    {
        SwapBuffers(*((HDC*)hDC)); 
        return;
    }

    while (Net->Current!=NULL)
    {
        ((CRow*)Net->Current)->Current = ((CRow*)Net->Current)->First;
        while (((CRow*)Net->Current)->Current != NULL)
        {    
            glBegin(GL_LINES);
			glColor3f(0.0f,(Net->Current == Net->GetFirst())?0.5f:0.8f,0.0f);
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY());
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX()+Wx*Net->GetSize(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY());        
            glEnd();
            glBegin(GL_LINES);
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX()+Wx*Net->GetSize(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY());
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX()+Wx*Net->GetSize(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY()+Wx*Net->GetSize());
            glEnd();
            glBegin(GL_LINES);
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX()+Wx*Net->GetSize(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY()+Wx*Net->GetSize());
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY()+Wx*Net->GetSize());
            glEnd();
            glBegin(GL_LINES);
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY()+Wx*Net->GetSize());
                glVertex2d(Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetX(),Wx*((CSquare*)((CRow*)Net->Current)->Current)->GetY());
            glEnd();
            ((CRow*)Net->Current)->Current = ((CRow*)Net->Current)->Current->GetNext();
        }  
        Net->Current = Net->Current->GetNext();
    };  

    
    
    Net->Current = CR;
    if (CR!=NULL)
    {
        ((CRow*)Net->Current)->Current = CS;
    }

    SwapBuffers(*((HDC*)hDC)); 
};*/

void DrawGraphics(HWND hWnd, void*&hDC, void *&hRC, CGraphic *_G)
{
	Resize(hWnd, hDC, hRC);

    RECT rect;
    GetClientRect(hWnd, &rect);
    OffsetRect(&rect, - rect.left, - rect.top);//move the co-ordinate beginning point to  the left-top corner of the window
    glViewport(rect.left, rect.top, rect.right, rect.bottom);//cut area to draw in it
    
    float Wx=(float)100.0*rect.right/rect.bottom;//width along Ox of the field
    float Wy=100.0;//width along Oy of the field;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(5);            
    glLoadIdentity();
    glTranslatef(-Wx,-Wy,-60.0f);

    glLineWidth(2); //width of the line
    glBegin(GL_LINES);//draw co-ordinate lines: Ox
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d(0,0); 
        glVertex2d(2*Wx,0); 
    glEnd();  
    glBegin(GL_LINES);//upper part of arrow Ox
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d((2)*Wx-3,1);
        glVertex2d(2*Wx,0); 
    glEnd();        
    glBegin(GL_LINES);//bottom part of arrow Ox
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d((2)*Wx-3,-1);
        glVertex2d(2*Wx,0); 
    glEnd();


    glBegin(GL_LINES);//draw co-ordinate lines: Oy
        glColor3d(0,0,0);    
        glVertex2d(0,0); 
        glVertex2d(0,2*Wy); 
    glEnd();
    glBegin(GL_LINES);//upper part of arrow Oy
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d(1,(2)*Wy-3);
        glVertex2d(0,2*Wy); 
    glEnd();        
    glBegin(GL_LINES);//bottom part of arrow Oy
        glColor3f(0.0f,0.0f,0.0f); 
        glVertex2d(-1,(2)*Wy-3);
        glVertex2d(0,2*Wy); 
    glEnd();
//search max x and max y;
    double maxX=0.1, maxY=0.1;
    
    for(DWORD i=0;i<_G->PointsNumber;i++)
    {
        if(maxX<fabs(_G->Points[i].X))
        {
            maxX=fabs(_G->Points[i].X);
        }
        if(maxY<fabs(_G->Points[i].Y))
        {
            maxY=fabs(_G->Points[i].Y);
        }
    }
    Wy=(float)(Wx*maxY/maxX);

    Wx*=2;
    Wy*=2;
    //end of search


    double x, y;
    if (_G->QuotientsNumber == 0)
	{
		glBegin(GL_LINES);//graphic of y=b;
			glColor3f(1,0,0);
			glVertex2d(0, Wy*_G->Quotients[0]/maxY);
			glVertex2d(Wx*(10000)/maxX, Wy*_G->Quotients[0]/maxY);
		glEnd();
	}
    else if (_G->QuotientsNumber == 1)
	{
		glBegin(GL_LINES);//graphic of y=k*x+b;
			glColor3f(1,0,0);
			glVertex2d(0, Wy*_G->Quotients[0]/maxY);
			glVertex2d(Wx*((-_G->Quotients[0])/_G->Quotients[1]+10000)/maxX, Wy*(10000*_G->Quotients[1])/maxY);
		glEnd();
	}
    else
    {
		glBegin(GL_LINES);//graphic of y=Sum:i from 0 to N {a[i]*x^i};
			glColor3f(1,0,0);
            x=0;
            y=Wy*_G->Quotients[0]/maxY;
            DWORD j;
            for (int i=0;i<100;i++)
            {
	            glVertex2d(Wx*x/maxX, Wy*y/maxY);
                x =maxX*i/100;
                y = 0;
                for (j=_G->QuotientsNumber+1;j>0;j--)
                {
                    y*=x;
                    y+=_G->Quotients[j-1];
                }
			    glVertex2d(Wx*x/maxX, Wy*y/maxY);
            }
		glEnd();
	}
    
    //points
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0,0,1);
    for(i=0;i<_G->PointsNumber;i++)
    {
        glVertex2d(Wx*_G->Points[i].X/maxX,Wy*_G->Points[i].Y/maxY);
    }
    glEnd();
    glDisable(GL_POINT_SMOOTH);
    //end points
    
    SwapBuffers(*((HDC*)hDC));
}

BOOL bSetupPixelFormat(HDC &hdc)
{

 GLuint PixelFormat;
 /*static  PIXELFORMATDESCRIPTOR pfd=
        {
                sizeof(PIXELFORMATDESCRIPTOR),  // Size of sruct
                1,                              // Version number (?)
                PFD_DRAW_TO_WINDOW |            // Window format
                PFD_SUPPORT_OPENGL |            // OpenGL support format
                PFD_DOUBLEBUFFER,               // with double buffer fomat
                PFD_TYPE_RGBA,                  // Color RGBA format
                16,                             // 16-bit depth of color
                0, 0, 0, 0, 0, 0,                       // ignore of color bites (?)
                0,                              // no transparency buffer
                0,                              // Ignore Shifting bit (?)
                0,                              // No Accu buffer
                0, 0, 0, 0,                             // Ignore Accu bites(?)
                16,                             // 16-bit mode of depth buffer 
                0,                              // no traffaret buffer
                0,                              // No suport buffers (?)
                PFD_MAIN_PLANE,                 // Main plane of draw
                0,                              // reserved (?)
                0, 0, 0                         // Ignore of masks of layers (?)
        };
		*/
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;

   PixelFormat = ChoosePixelFormat(hdc, &pfd);
                        // Get similar format a pixel from system

   SetPixelFormat(hdc,PixelFormat,&pfd);


   return TRUE;
}

//accelerated graphics

void DrawAccPicture(HWND hWnd,void*&hDC, void *&hRC, TImage &picture, CLayer *First)
{
	DrawPicture(hWnd,hDC,hRC,picture);
	DrawLayers(hWnd,hDC,hRC,First);
	    SwapBuffers(*((HDC*)hDC));	
};
void DrawAccColorPicture(HWND hWnd, void*&hDC, void *&hRC, TColorImage &picture, CLayer *First)                   //drawing function for color picture
{
	DrawColorPicture(hWnd,hDC,hRC,picture);
	DrawLayers(hWnd,hDC,hRC,First);
	    SwapBuffers(*((HDC*)hDC));	
}

void DrawAccGraphics(HWND hWnd, void*&hDC, void *&hRC, CGraphic *);									//drawing function
void DrawAccLayers(HWND hWnd, void*&hDC, void *&hRC, CLayer *First)
{
		Resize(hWnd, hDC, hRC);
    RECT rect;
    GetClientRect(hWnd, &rect);
    OffsetRect(&rect, - rect.left, - rect.top);   //move the co-ordinate beginning point to  the left-top corner of the window
    glViewport(rect.left, rect.top, rect.right, rect.bottom);   //cut area to draw in it
    
    float Wy=200.0;   //width along Oy of the field;
    float Wx=(float)Wy*rect.right/rect.bottom;  //width along Ox of the field
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
    glTranslatef(-Wx/2,-Wy/2,-60.0f);

    glEnable(GL_POINT_SMOOTH);
	DrawLayers(hWnd,hDC,hRC,First);
	glDisable(GL_POINT_SMOOTH);

    SwapBuffers(*((HDC*)hDC));	

}
void DrawLayers(HWND hWnd, void*&hDC, void *&hRC, CLayer *First)
{
//	Resize(hWnd, hDC, hRC);
 //   RECT rect;
 //   GetClientRect(hWnd, &rect);
 //   OffsetRect(&rect, - rect.left, - rect.top);   //move the co-ordinate beginning point to  the left-top corner of the window
 //   glViewport(rect.left, rect.top, rect.right, rect.bottom);   //cut area to draw in it
    
 //   float Wy=200.0;   //width along Oy of the field;
 //   float Wx=(float)Wy*rect.right/rect.bottom;  //width along Ox of the field
 
 //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //  glLoadIdentity();
 //   glTranslatef(-Wx/2,-Wy/2,-60.0f);

 //   glEnable(GL_POINT_SMOOTH);
//	glBegin(GL_POINTS);
	   //glVertex3f(0,0,0);
	//glEnd();
	while(First)
	{
		if (First->Draw) 
		{
			glVertexPointer(2, GL_DOUBLE, 0, (void*)(First->Points));
			glEnableClientState(GL_VERTEX_ARRAY);
			if (First->Type==CLayer::ltPolygon)
				glDrawArrays(GL_LINE_LOOP, 0, First->PointsNumber);
			if (First->Type==CLayer::ltPoints)
				glDrawArrays(GL_POINTS, 0, First->PointsNumber);
		}
		First = (CLayer*)First->GetNext();
	}

//	glDisable(GL_POINT_SMOOTH);

   // SwapBuffers(*((HDC*)hDC));	


}


