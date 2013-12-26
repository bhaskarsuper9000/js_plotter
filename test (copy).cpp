#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point
{

public:
    float x,y,z;

    Point()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Point(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }

    Point (const Point& p)
    {
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
    }

    Point operator + (const Point& p){
        float tp_x = this->x + p.x;
        float tp_y = this->y + p.y;
        float tp_z = this->z + p.z;

        return Point(tp_x, tp_y, tp_z);
    }

    Point operator - (const Point& p){
        float tp_x = this->x - p.x;
        float tp_y = this->y - p.y;
        float tp_z = this->z - p.z;

        return Point(tp_x, tp_y, tp_z);
    }

    friend ostream &operator<<(ostream &out, Point p)     //output
    {
            out<<"X = "<<p.x<<" Y = "<<p.y <<" Z = "<<p.z;
            return out;
    }

    friend istream &operator>>(istream &in, Point &p)     //input
    {
            cout<<"Enter X: ";
            in>>p.x;
            cout<<"Enter Y: ";
            in>>p.y;
            cout<<"Enter Z: ";
            in>>p.z;
            return in;
    }

    void swap(int n)
    {
        float temp;
        switch(n)
        {
        case 1:
            temp = x;
            x = z;
            z = temp;
            break;
        case 2:
            temp = x;
            x = y;
            y = temp;
            break;
        case 3:
            temp = z;
            z = x;
            x = temp;
            temp = x;
            x = y;
            y = temp;
            break;
        case 4:
            temp = y;
            y = z;
            z = temp;
            break;
        case 5:
            temp = z;
            z = x;
            x = temp;
            temp = y;
            y = z;
            z = temp;
            break;
        case 6:
            //Nothing to be done
            break;
        }
    }
};

class SimplePathInterpolator
{
    float scaleFactor;
    float interpolationFactor;
    float SLOPE_THRESHOLD;

public:
    vector<Point> pVect;

    SimplePathInterpolator(float sFac, float iFac, float deg){
        scaleFactor = sFac;
        interpolationFactor = iFac;
        SLOPE_THRESHOLD = tan(deg * M_PI / 180);
    }

    void add(Point &p)
    {
        pVect.push_back(p);
    }

    //    Dec   a>b b>c c>a
    //     0    0	0	0	c>b>a	Not possible
    //     1    0	0	1	c>b>a
    //     2    0	1	0	b>a>c
    //     3    0	1	1	b>c>a
    //     4    1	0	0	a>c>b
    //     5    1	0	1	c>a>b
    //     6    1	1	0	a>b>c
    //     7    1	1	1	a>b		Not possible

    void interpolate_internal(float a, float b, float c, Point dest, Point src)
    {
        float slope_x = a/interpolationFactor;
        float slope_y = b/interpolationFactor;
        float slope_z = c/interpolationFactor;

        /*
        if(slope_x > SLOPE_THRESHOLD)
        {
            cout<<"x shoot";
        }
        if(slope_y > SLOPE_THRESHOLD)
        {
            cout<<"y shoot";
        }
        if(slope_z > SLOPE_THRESHOLD)
        {
            cout<<"z shoot";
        }
        */
        cout<<"Inside Interpolate Internal";
        cout<<src<<dest<<endl;

        cout<<"Interpolating";
        if(dest.x > src.x){

            float y_factor;
            float z_factor;

            if(dest.y > src.y)
                y_factor = interpolationFactor*(dest.y - src.y)/(dest.x - src.x);
            else
                y_factor = -interpolationFactor*(src.y - dest.y)/(dest.x - src.x);

            if(dest.z > src.z)
                z_factor = interpolationFactor*(dest.z - src.z)/(dest.x - src.x);
            else
                z_factor = -interpolationFactor*(src.z - dest.z)/(dest.x - src.x);

            cout<<endl<<"\n\ny_factor"<<y_factor<<"\nz_factor= "<<z_factor<<endl;

            for(float i=src.x, j=src.y, k=src.z; i<=dest.x; i+=interpolationFactor, j+=y_factor, k+=z_factor )
            {
                //pVect.push_back(Point(i));
                cout<<i<<" "<<j<<" "<<k<<" "<<endl;
            }
        }
        else
        {
            for(float i=dest.x; i>=src.x; i-=interpolationFactor )
            {
                //pVect.push_back(Point(i));
                cout<<i<<""<<""<<endl;
            }
        }
        cout<<"Finished Interpolating";
    }

    vector<Point> interpolate(Point& dest, Point& src)
    {
        //first check which set of co-ords have max diff
        float a = dest.x - src.x;
        float b = dest.y - src.y;
        float c = dest.z - src.z;

        cout<<Point(a,b,c)<<endl;

        bool a_vs_b = (abs(a)>abs(b))?true:false;
        bool b_vs_c = (abs(b)>abs(c))?true:false;
        bool c_vs_a = (abs(c)>abs(a))?true:false;


        int grt = (int)a_vs_b<<2 | b_vs_c<<1 | c_vs_a;
        cout<<grt<<endl;

        //cout<<ag<<" "<<bg<<" "<<cg<<" "<<endl;

        switch(grt)
        {for(int i=src.x; i<=dest.x; i+=interpolationFactor )
        {
            //pVect.push_back(Point(i));
            cout<<i;
        }
        case 1:
            cout<<"c>b>a";
            src.swap(1);
            dest.swap(1);
            interpolate_internal(c,b,a,dest,src);
            break;
        case 2:
            cout<<"b>a>c";
            src.swap(2);
            dest.swap(2);
            interpolate_internal(b,a,c,dest,src);
            break;
        case 3:
            cout<<"b>c>a";
            src.swap(3);
            dest.swap(3);
            interpolate_internal(b,c,a,dest,src);
            break;
        case 4:
            cout<<"a>c>b";
            src.swap(4);
            dest.swap(4);
            interpolate_internal(a,c,b,dest,src);
            break;
        case 5:
            cout<<"c>a>b";
            src.swap(5);
            dest.swap(5);
            interpolate_internal(c,a,b,dest,src);
            break;
        case 6:
            cout<<"a>b>c";
            src.swap(6);
            dest.swap(6);
            interpolate_internal(a,b,c,dest,src);
            break;
        }
        cout<<endl;

        //Swap the interpolated points

        return pVect;

    }

};

int main()
{
    Point p(10, 20, 20);
    Point q(10.34, 12.5, 99.01);

    //std::cin>>p;

    cout<<p<<endl<<q<<endl;
    Point r = p + q;

    cout<<r<<endl;


    vector<Point> pVect;
    pVect.push_back(p);
    pVect.push_back(r);
    pVect.push_back(q);

    vector<Point>::const_iterator i;
    for(i=pVect.begin(); i!=pVect.end(); ++i)
    {
        cout << *i << endl;
    }

    SimplePathInterpolator spi(10,34,45);
    spi.interpolate(q,p);

    return 0;
}
