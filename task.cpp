#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<vector>

#define mp make_pair
#define pdd pair<double,double>
#define vpdd vector<pdd>
#define sz size
#define fi first
#define se second
#define pb push_back


using namespace std;
// task1

double y(const double x, const double A, const double phi, const double f){
    return A*sin(2*M_PI*x*f+phi);
}

vpdd generator(const double f, const double start = -5, const double finish = 5, const double A=10, const double phi=0,const double dt = 0.01){
    vpdd res;
    for (double x = start; x<=finish; x+=dt)
        res.pb(make_pair(x,y(x,A,phi,f)));
    return res;
}

// task 2

double L(double x,const vpdd& v){
    double res = 0;
    for (int i =0;i<v.sz();++i){
        double l = 1;
        for (int j = 0;j<v.sz();++j)
            if (i!=j)
                l*=(x-v[j].fi)/(v[i].fi-v[j].fi);
        res+=v[i].se*l;
    }
    return res;
}

vpdd interpolation(const vpdd& v){
    vpdd res;
    int n = v.sz();
    vpdd tmp = {v[0],v[1],v[2]};
    double x = (v[0].fi+v[1].fi)/2;
    res.pb(v[0]);
    res.pb(mp(x,L(x,tmp)));
    for (int i = 1;i<n-1;++i){
        tmp = {v[i-1],v[i],v[i+1]};
        x = (v[i].fi+v[i+1].fi)/2;
        res.pb(v[i]);
        res.pb(mp(x,L(x,tmp)));
    }
    res.pb(v.back());
    return res;
}

//task 3

vpdd decimation(const vpdd& v, int h){
    vpdd res;
    for (int i = 0;i<v.sz();i+=h)
        res.pb(v[i]);
    return res;
}

// task 4

vector<double> get_vector(const vpdd& v, int h){
    vpdd new_v = interpolation(decimation(v,h));
    vector<double> res(v.sz());
    for (int i = 0;i<v.sz();++i)
        res[i] = new_v[i].se - v[i].se;
    return res;
}

double average(const vector<double> &v){
    double res = 0;
    for (double e: v)
        res+=e;
    res/=v.sz();
    return res;
}

double MSE(const vector<double> &v){
    double res = 0;
    double avg = average(v);
    for (double e: v)
        res+=(e-avg)*(e-avg);
    res/=(v.sz());
    return res;
}

int main(){
    freopen("result.csv","w",stdout);
    for (int i = 0;i<51;++i){
        vector<double> v = get_vector(generator(i),2);
        cout<<i<<' '<<MSE(v)<<'\n';
    }

    return 0;
}
