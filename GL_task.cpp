#include <QCoreApplication>
#include <iostream> //Including this header may automatically include other headers
#include <fstream> //Input stream objects can read and interpret input from sequences of characters.
#include <pwd.h> //header provides a definition for struct passwd
#include <unistd.h> //is the name of the header file that provides access to the POSIX operating system API
#include <sys/sysinfo.h> //return system information
#include <string> //Strings are objects that represent sequences of characters.

using namespace std;

void update();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    while(true)
    {
        update();
        sleep(10); //-----wait 10 seconds
        system("clear"); // all clear and cycle again
    }



    cin.get();
    return a.exec();
}

void update()
{

    //---------------output data of hostname and data name

    ifstream stream("/proc/sys/kernel/hostname"); string str;
        getline(stream,str); cout<<"Hostname: "<<str<<endl;

    uid_t uid = geteuid();
    passwd *pw = getpwuid(uid);
    cout<<"Username: "<<pw->pw_name<<endl;

    struct sysinfo o;
    sysinfo(&o);
    long up = o.uptime;
    long procs = o.procs;
    int hour = up/60/60;
    int min = (up - hour*60*60) / 60;
    int sec =  ((up - hour*60*60) - min*60);
    cout<<"\nUptime: "<<hour<<" h. "<<min<<" m. "<<sec<<" s. ";


    //-------------output number of processes and all about CPU

    cout<<"\nNumber of processes: "<<procs;

    stream.close();
    stream.open("/proc/cpuinfo");

    for(int i = 0; i < 16;i++)
        stream >> str;
    getline(stream,str);
    cout<<"\nCPU: "<<str<<endl;

    for(int i = 0; i< 10; i++)
        stream >> str;
    cout<<"CPU usage "<<str<<" MHz  ";
    cout<<atoi(str.c_str())/23.0<<"%";

    //---------------output all about RAM

    stream.close(); stream.open("/proc/meminfo");
    stream >> str; stream >> str;
    int num = atoi(str.c_str());

    int percent = num / 100;

    int gb = (num / 1024) / 1024;
    int mb = (num-gb*1024*1024) /1024;
    int kb = (num - (gb*1024*1024+mb*1024));

    cout<<"\nRAM: ";
    if (gb > 0)
       cout<<gb<<" Gb ";
    if (mb > 0)
       cout<<mb<<" Mb ";
    if (kb > 0)
       cout<<kb<<" Kb ";

    int free = 0;
    for (int i = 0 ; i < 3 ; i++) {
        stream >> str; stream >> str; stream>>str;
        free += atoi(str.c_str());
    }
    num -= free;
    gb = num / 1024 / 1024;
    mb = (num - gb*1024*1024) / 1024;
    kb = (num - ((mb*1024) + (gb * 1024 * 1024)));
    cout<<num;
    cout<<"\nRAM usage: ";
    if (gb > 0)
       cout<<gb<<" Gb ";
    if (mb > 0)
       cout<<mb<<" Mb ";
    if (kb > 0)
       cout<<kb<<" Kb ";
    cout<<"  "<<num/percent<<"%\n";


}

