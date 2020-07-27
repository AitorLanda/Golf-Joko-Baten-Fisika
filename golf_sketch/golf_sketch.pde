int rad = 10;        // Width of the shape
float xpos, ypos;    // Starting position of shape    

float xspeed = 2.2;  // Speed of the shape
float yspeed = 2.8;  // Speed of the shape
float tiempo=0;
float v0=40;
float angelua=45;
float x0=0;
float y0=0;
float v1=0;
float vx, m = 0.00468673469387755102040816326531, restituzioa;

void setup() 
{
  size(640, 360);
  noStroke();
  frameRate(30);
  
  xpos = 0;
  ypos = 360;

}

void draw() 
{
  float angeluaRad;
  float xPantaila, yPantaila;
  float yMax;
  float tMax;
  background(102);
  angeluaRad= radianetara(angelua);
  yMax=Ymax (v0, angeluaRad);
  
  xpos = XBerri(tiempo, v0,  angeluaRad,  x0);      
  ypos = YBerri(tiempo, v0,  angeluaRad,  y0);
  tMax= Tmax(angeluaRad, v0);
  xPantaila= xPantaila(xpos);
  yPantaila= yPantaila(ypos);
  ellipse(xPantaila, yPantaila, rad, rad);
  tiempo+=0.1;
  if (ypos<0)
  erreboteak(yMax, tMax);  //<>//
}

void erreboteak(float yMax, float tMax)
{
  v1=Vbajada(yMax,m);
  restituzioa = r(v0, tMax);
  yMax=erreboteAltuera(yMax, restituzioa);
  x0=xpos;
  v0=v0*r(v0,tiempo);
  tiempo=0;
}

float XBerri(float t, float v, float angelua, float x0)
{
  float x;
  
  x = x0+v*cos(angelua)*t;
  return x;
}
float YBerri(float t, float v, float angelua, float y0)
{
  float y;
  y = y0 + (v * sin(angelua) * t-0.5 * 9.8 * pow(t,2));
  return y;
}  
float radianetara(float angelua)
{
  float radianak;
  radianak = (angelua*PI) / 180;
  return radianak;
}
float xPantaila (float x)
{
  float xRef=0;
  int direccion=1;
  float ret=0;
  ret=(x-xRef)*direccion;
  return ret;
}
float yPantaila (float y)
{
  float yRef=360;
  int direccion=-1;
  float ret=0;
  ret=(y-yRef)*direccion;
  return ret;
}

float Ymax(float v, float angelua)
{
  float Y;
  Y = (v*v*sin(angelua)*sin(angelua))/(2*9.8);
  return Y;
}
float Tmax(float angelua, float v)
{
  float g = 9.8, tmax;
  tmax = (2 * v*sin(angelua)) / g;
  return tmax;
}
float Vbajada(float y, float m)
{
  float ep, ez, Vbajada;
    ep = m*9.8*y;
    ez = ep;
    Vbajada = sqrt(ez / (m*0.5));
  return Vbajada;
}
float erreboteAltuera(float y, float e)
{
  float h;
  h = e*y;
  return h;
}
float r(float v, float t)
{
  float e, g = 9.8;
  e = 1 / (1 + (2 * v) / (g*t));
  return e;
}