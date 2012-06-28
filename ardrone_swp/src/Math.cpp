#include "Math.h"
#include "Global.h"
#include "ardrone_brown/Navdata.h"


namespace
{
	void center(const ar_recog::Tag& tag, float& cx, float& cy, float dx, float dy, float width, float height);
}

/* @brief Berechnung der Anzahl der Pixel, um die das Tag aufgrund der Rotation verschoben wurde
 *
 * Problem: Sichtfeld ist noch nicht korrekt berechnet(derzeit für x und y Richtung gleich)
 *
 */
void Math::pixelDiffBottom(float& x, float& y)
{

	  /*float ds = altd * tan( roty );  //Entfernung eingentliche position vom Tag (y) zur ermittelten
	  float c = (2 * altd) / tan(58); //Sichtfeldgröße
	  y = (ds * height) / c;      //Punkte des Tags werden um diese anzahl von Pixeln verschoben

	  float dsx = altd * tan( rotx );
	  x = (dsx * width) / c;

	  x /= 3;
	  y *= 0.5;

	  	  ostr << "roty     " << roty << endl;
	  ostr << "Delta s: " << ds << endl;
	  ostr << "c        " << c << endl;
	  ostr << "dy       " << dy << endl;
	  ostr << "delt s:  " << dsx << endl;
	  ostr << "dx       " << dx << endl;
	  */

	y = 0.5 * tan(Cglobal::instance().roty) * 1.6 * Cglobal::instance().heightB;  //tan(58)~= 1.6
	x = 0.5 * tan(Cglobal::instance().rotx) * 1.6 * Cglobal::instance().widthB;
}

void Math::pixelDiffFront(float& x, float& y)
{

	y = 0.5 * tan(Cglobal::instance().roty) * 0.948965 * Cglobal::instance().heightF;  //tan(43.5)~= 0.948965
	x = 0.5 * tan(Cglobal::instance().rotx) * 0.948965 * Cglobal::instance().widthF;
}

/* @brief Berechnung aus den Eckpunkten wo sich das Tag bezüglich des Bildes befindet

	cy: 0 Tag ist am oberen Bildrand, 0.5 Tag ist in der Mitte(Höhe), 1 Tag ist am unteren Bildrand
	cx: 0 Tag ist am linken Bildrand, 0.5 Tag ist in der Mitte(Breite), 1 Tag ist am rechten Bildrend
*/
void Math::centerBottom(const ar_recog::Tag& tag, float& cx, float& cy)
{
	float dx, dy;
	pixelDiffBottom(dx,dy);
	center(tag, cx, cy, dx, dy, Cglobal::instance().widthB, Cglobal::instance().heightB);
}

void Math::centerFront(const ar_recog::Tag& tag, float& cx, float& cy)
{
	float dx, dy;
	pixelDiffFront(dx,dy);
	center(tag, cx, cy, dx, dy, Cglobal::instance().widthF, Cglobal::instance().heightF);
}

/* @brief subscriber handler für die Nachricht /ardrone/navdata
 *
 * speichert die Navdata-Informationen
 */
void Math::navdataUpdate(const ardrone_brown::Navdata::ConstPtr& navdata)
{
	Cglobal::instance().altd = navdata->altd;
	Cglobal::instance().vx = navdata->vx;
	Cglobal::instance().vy = navdata->vy;
	Cglobal::instance().vz = navdata->vz;
	Cglobal::instance().roty = (navdata->rotY) * 0.017453f;  //grad in rad umrechnen
	Cglobal::instance().rotx = (navdata->rotX) * 0.017453f;
}

namespace
{
	void center(const ar_recog::Tag& tag, float& cx, float& cy, float dx, float dy, float width, float height)
	{
		cx = 0;
		cy = 0;
		for(int i = 0; i < 7; i+=2)
		{
			cx = cx + tag.cwCorners[i];
			cy = cy + tag.cwCorners[i+1];
		}
		cy = cy / 4.0;
		cy += dy;
		cy = cy / height;

		cx = cx / 4.0;
		//cx -= dx;
		cx += dx;
		cx = cx / width;
	}
}