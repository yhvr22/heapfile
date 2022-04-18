#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef long long ll;
#define inf std::numeric_limits<int>::max()
#define pb push_back
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
int pgsize;

class record{
    private:
        int size;
        int key;
    public:
        record(int sz,int pk){size=sz;key=pk;}
        int getsize(){return size;}
        int getkey(){return key;}
};

class page{
    private:
        int count;
        int freespace;
        vector<record*> rec;
    public:
        page(){
            count=0;
            freespace=pgsize-4*4;
        }
        bool insert(record* R){
            int sz=R->getsize();
            int key=R->getkey();
            if(sz+4 <= freespace){
                count++;
                rec.push_back(R);
                freespace-=R->getsize()+4;
                return 1;
            }
            return 0;
        }
        int search(int k){
            for(int i=0; i<rec.size(); i++)
                if(rec[i]->getkey()==k)
                    return i;
            return -1;
        }
        int getcount(){return count;}
        int getfreespace(){return freespace;}
        void printallrecords(){
             for(int i=0; i<rec.size(); i++){
                cout<<rec[i]->getkey()<<" ";
             }
        }
    
};
class Heap{
    private:
        list<page> pages;
        vector<page*> dir;
    public:
        Heap(){}
        bool insert(int size, int key){
            if(pages.empty()){
                page *p0=new page();
                pages.push_back(*p0);
                dir.pb(p0);
            }
            record* r=new record(size,key);
            list<page>::iterator i;
            for(i=pages.begin();i!=pages.end();i++){
                if(i->insert(r))
                    return 1;
            }
            page *p1=new page();
            pages.push_back(*p1);
            dir.pb(p1);
            if(pages.back().insert(r)){return 1;}
            return 0;
        }
        void search(int key){
            bool found=false;
            int count;
            list<page>::iterator i;
            for(i=pages.begin();i!=pages.end();i++){
                int p=i->search(key);
                if(p!=-1){
                    cout<<count<<" "<<p<<endl;
                    return;
                }
                count++;
            }
            cout<<"-1 -1"<<endl;
        }
        void status(){
            int sz=pages.size();
            cout<<sz<<" ";
            list<page>::iterator i;
            for(i=pages.begin();i!=pages.end();i++){
                cout<<i->getcount()<<" ";
            }cout<<endl;
        }
        void printfreespaces(){
            list<page>::iterator i;
            for(i=pages.begin();i!=pages.end();i++){
                cout<<i->getfreespace()<<" ";
            }cout<<endl;
        }
        void printallkeys(){
            list<page>::iterator i;
            for(i=pages.begin();i!=pages.end();i++){
                i->printallrecords();cout<<"\n";
            }cout<<endl;
        }
};


signed main(){
    FAST_IO
    cin>>pgsize;
    //pgsize=100;
    Heap H;
    //p1->print();
    int x;
    while(cin>>x){
        switch(x){
            case 1: int y,z; cin>>y>>z; H.insert(y,z);break;
            case 2: H.status();break;
            case 3: int a;cin>>a;H.search(a);break;
            case 4: goto end;
            case 5: H.printfreespaces();break;
            case 6: H.printallkeys();break;
            
            default: break;
        }
    }
    end:
    return 0;
}
