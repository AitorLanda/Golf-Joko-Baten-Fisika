#define _CRT_SECURE_NO_WARNINGS
#define PI 3.141592
#define MU 0.3
#include <stdio.h>
#include <string.h>
#include <math.h>
/*Berez golf zelai baten 'x' maximoa ((0,0)posiziotik zuloaraino), 5000m distantzia dago, pantailaren mugak direla eta, 640  izango litzateke,
baina guk .c kode honetan bakarrik kontuan hartu ditugu neurri maximoak*/

double Xmax(double v, double angelua);  //Alcance máximo (solo en la parabola del tiro)
double Ymax(double v, double angelua);  //Altura máximo (solo en la parabola del tiro), en los rebotes se sustituye por "erreboteAltuera"
double XBerri(double t, double v, double angelua, double x); //Cada punto en el eje X de la parabola cada 0.1s
double YBerri(double y0, double t, double v, double angelua); //Cada punto en el eje Y de la parabola cada 0.1s
double radianetara(double radianetara); //Pasar el angulo de º a radianes
double Tmax(double angelua, double v); //El tiempo que está la pelota en el aire
double Vbajada(double y, double m, double x); //La velocidad de la pelota antes de tocar el suelo
double erreboteAltuera(double y, double restituzioa); //La altura (máxima) del rebote
double r(double v, double t);  //Coeficiente de restitución
double VX(double v1, double angelua); //Abiadura X ardatzan, hurrengo funtziorako erabilgarria.
double rodamendua(double vx, double m); //Pilota egiten duen desplazamendua boteak eman ondoren, marruskadura gelditu arte.
void erreboteak(double x, double x0, double y, double x1, double y1, double t, double v, double v1, double tmax, double m, double restituzioa, double angelua, double y0, double vx);
int main(int argc, char* argv[])
{
  double x=0, vx=0, x0 = 0, y=0, x1=0, y1=0, y0 = 0, t = 0, v=0, v1=0, tmax=0, m = 0.00468673469387755102040816326531, restituzioa=0, angelua=0;
  char str[128];
  erreboteak(x, x0, y, x1, y1, t, v, v1, tmax, m, restituzioa, angelua, y0, vx);
  printf("\n\n");
  printf("Sakatu \"return\" amaitzeko .....");
  fgets(str, 128, stdin);
  return 0;
}

double Xmax(double v, double angelua)
{
  double X;
  X = (v*v * 2 * sin(angelua)*cos(angelua)) / (9.8);
  return X;
}
double Ymax(double v, double angelua)
{
  double Y;
  Y = (v*v*sin(angelua)*sin(angelua))/(2*9.8);
  return Y;
}
double XBerri(double t, double v, double angelua, double x0)
{
  double x;
  x = x0+v*cos(angelua)*t;
  return x;
}
double YBerri(double y0, double t, double v, double angelua)
{
  double y;
  y = y0 + v*sin(angelua)*t-0.5*9.8*pow(t,2);
  return y;
}
double Tmax(double angelua, double v)
{
  double g = 9.8, tmax;
  tmax = (2 * v*sin(angelua)) / g;
  return tmax;
}
double radianetara(double angelua)
{
  double radianak;
  radianak = (angelua*PI) / 180;
  return radianak;
}
double Vbajada(double y, double m, double x)
{
  double ep, ez, Vbajada;
    ep = m*9.8*y;
    ez = ep;
    Vbajada = sqrt(ez / (m*0.5));
  return Vbajada;
}
double erreboteAltuera(double y, double e)
{
  double h, g=9.8;
  h = e*y;
  return h;
}
double r(double v, double t)
{
  double e, g = 9.8;
  e = 1 / (1 + (2 * v) / (g*t));
  return e;
}
double VX(double v1, double angelua)
{
  double vx;
  vx = v1*cos(angelua);
  return vx; 
}
double rodamendua(double vx, double m)
{
  double d;
  d = (7 * m*pow(vx, 2)) / (10 * MU*m*9.8);
  return d;
}
void erreboteak(double x, double x0, double y, double x1, double y1, double t, double v, double v1, double tmax, double m, double restituzioa,  double angelua, double y0, double vx)
{
  char str[128];
  printf("Emaidazu hurrengo balioak:\n");
  printf("Pilota jaurtitzeko angelua: \n");
  fgets(str, 128, stdin);
  sscanf(str, "%lf", &angelua);
  angelua = radianetara(angelua);
  printf("Pilota jaurtitzeko hasierako abiadura: \n");
  fgets(str, 128, stdin);
  sscanf(str, "%lf", &v);
  tmax = Tmax(angelua, v);
  v1 = Vbajada(y, m, x);
  x0 = x1;
  restituzioa = r(v, tmax);
  t = 0;
  do
  {
    x1 = XBerri(t, v, angelua, x0);
    y1 = YBerri(y0, t, v, angelua);
    t = t + 0.01;
    printf("(%lf, %lf)\n", x1, y1);
  } while (t <= tmax);
  printf("\n\n \t----- ERREBOTEA ----- \n\n");
  do {
    v1 = Vbajada(y, m, x);
    y = erreboteAltuera(y, restituzioa);
    x0 = x1;
    v = v*r(v, t);
    t = 0;
    tmax = Tmax(angelua, v);
    y = Ymax(v, angelua);
    do
    {
      x1 = XBerri(t, v, angelua, x0);
      y1 = YBerri(y0, t, v, angelua);
      t = t + 0.01;
      printf("(%lf, %lf)\n", x1, y1);
    } while (t <= tmax);
    printf("\n\n \t----- ERREBOTEA ----- \n\n");
    if (x1 > 5010)
      break;
  } while (y1 > 0.01);
  vx = VX(v1, angelua);
  x1 += rodamendua(vx, m);

  if ((x1 == 5000 && y1 == 0) || (x1 > 4999.99 && y1 < 0.02) && (x1 < 5000.1 && y1 < 0.02))
    printf("\tZorionak! Zuloan sartu duzu pilota");
  else if (x1 > 5010)
    printf("Zulotik pasa zara, eta golf pilota laku batera erori da.\n \tJokoa amaitu da.\n");
  else if (5010 > x1 && x1 > 5000.1)
  {
    double AX = 0;
    AX = 5000 - x1;
    printf("Pixka bat pasatu zara, baina oraindik Green-ean zaude, zulotik %lfm-tara. \n", AX);
    erreboteak(x, x0, y, x1, y1, t, v, v1, tmax, m, restituzioa, angelua, y0,vx);
  }
  else
  {
    double AX = 0;
    AX = 5000 - x1;
    printf("Oraindik %.3lfm-tara zaude zuloarekiko, eman beste golpe bat. \n", AX);
    erreboteak(x, x0, y, x1, y1, t, v, v1, tmax, m, restituzioa, angelua, y0,vx);
  }
}