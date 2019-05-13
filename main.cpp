#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "Customer.h"
#include "Cashier.h"
#include "Barista.h"
#include <vector>
#include <queue>
#include <iomanip>


using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}
struct CompareCurrentTime {
    bool operator()(Customer const & c1, Customer const & c2) {
        // return "true" if "c1" is ordered before "c2", for example:
        return c1.currentTime > c2.currentTime;
    }
};
struct CompareArrivalTime {
    bool operator()(Customer const & c1, Customer const & c2) {
        // return "true" if "c1" is ordered before "c2", for example:
        return c1.arrivalTime > c2.arrivalTime;
    }
};
struct ComparePrice {
    bool operator()(Customer const & c1, Customer const & c2) {
        // return "true" if "p1" is ordered before "p2", for example:
        return c1.price < c2.price;
    }
};
int main(int argc, char* argv[]) {
    // below reads the input file
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;
    ifstream infile(argv[1]);
    string line;
    vector<string> input;
    // process first line
    getline(infile, line);
    int cashierNumber = stoi(line);
    getline(infile, line);
    int customerNumber= stoi(line);
    int baristaNumber=cashierNumber/3;
    vector<Cashier> cashiers=*new vector<Cashier>(cashierNumber);
    //I created two different customer arrays because I have to use same customers twice, each for both models.
    vector<Customer> customers1=*new vector<Customer>(customerNumber);
    vector<Customer> customers2=*new vector<Customer>(customerNumber);
    int maxLengthBaristaQ=0;
    int maxLengthCashierQ=0;
    double model1Finish=0;
    vector<Barista> baristas=*new vector<Barista>(baristaNumber);
    priority_queue<Customer, vector<Customer>, CompareCurrentTime> timeline1;
    priority_queue<Customer, vector<Customer>, CompareCurrentTime> timeline2;
    //Below I'm taking customers from file and adding them to vectors customers1 and 2. Every customer that is created is pushed to the timelines.
    for(int i=0;i<customerNumber;i++){
        getline(infile, line);
        vector<string> words;
        split1(line,words);
        double at=stod(words[0]);
        double ot=stod(words[1]);
        double bt=stod(words[2]);
        double pri=stod(words[3]);
        Customer a=*new Customer(at,pri,ot,bt);
        Customer b=*new Customer(at,pri,ot,bt);
        a.index=i;
        b.index=i;
        customers1[i]=a;
        customers2[i]=b;
        timeline1.push(a);
        timeline2.push(b);
    }
    //for model1
    priority_queue<Customer, vector<Customer>, CompareArrivalTime> cashierQueue;
    priority_queue<Customer, vector<Customer>, ComparePrice> baristaQueue;
    //positions 0:arrived 1:onCashierQueue 2:ordering 3:baristaQueue 4:brewing
    while(!timeline1.empty()){
        Customer current=timeline1.top();
        timeline1.pop();
        if(current.position==0){
            //Here, the customer on timeline is just arrived.
            bool hasFoundCashier=false;
            for(int i=0;i<cashierNumber;i++){
                //Checking if there is empty cashier, if there is one, we send the customer there.
                if(cashiers[i].currentCustomer== nullptr){
                    cashiers[i].takeCustomer(current);
                    current.cashier=i;
                    timeline1.push(current);
                    hasFoundCashier=true;
                    break;
                }
            }
            if(!hasFoundCashier){
                //if there is not an empty cashier, we send customer to cashier queue and update the max length
                cashierQueue.push(current);
                current.position=1;
                if(cashierQueue.size()>maxLengthCashierQ)
                    maxLengthCashierQ=cashierQueue.size();
            }
        }else if(current.position==2){
            //here, the customer is finised ordering
            int cashierIndex=current.cashier;
            cashiers[cashierIndex].giveCustomer();
            if(!cashierQueue.empty()){
                //we are taking the customer from that cashier and if there is a customer on queue, we put it on the emptied cashier.
                Customer n=cashierQueue.top();
                n.currentTime=current.currentTime;
                cashierQueue.pop();
                cashiers[cashierIndex].takeCustomer(n);
                n.cashier=cashierIndex;
                timeline1.push(n);
            }
            bool hasFoundBarista=false;
            for(int i=0;i<baristaNumber;i++){
                //Now, we are looking for a empty barista. If there is one, we put the customer in it.
                if(baristas[i].currentCustomer== nullptr){
                    baristas[i].takeCustomer(current);
                    current.barista=i;
                    timeline1.push(current);
                    hasFoundBarista=true;
                    break;
                }
            }
            if(!hasFoundBarista){
                //If there is not an empty barista, we put our customer on the barista queue
                baristaQueue.push(current);
                current.position=3;
                if(baristaQueue.size()>maxLengthBaristaQ)
                    maxLengthBaristaQ=baristaQueue.size();
            }
        }else if(current.position==4){
            //when our customer's coffee is ready, we empty its barista and update the finish time
            int baristaIndex=current.barista;
            baristas[baristaIndex].giveCustomer();
            customers1[current.index].finishTime=current.currentTime;
            model1Finish=current.currentTime;
            if(!baristaQueue.empty()){
                //If there is another customer on baristaqueue we take it then put it on our emptied barista.
                Customer n=baristaQueue.top();
                n.currentTime=current.currentTime;
                baristaQueue.pop();
                baristas[baristaIndex].takeCustomer(n);
                n.barista=baristaIndex;
                timeline1.push(n);
            }
        }
    }

    freopen (argv[2],"w",stdout);
    printf("%.2lf \n",model1Finish);
    printf("%d \n",maxLengthCashierQ);
    printf("%d \n",maxLengthBaristaQ);
    for(int i=0;i<cashierNumber;i++){
        printf("%.2lf \n",cashiers[i].totalWorkTime/model1Finish);
    }
    for(int i=0;i<baristaNumber;i++){
        printf("%.2lf \n",baristas[i].totalWorkTime/model1Finish);
    }
    for(int i=0;i<customerNumber;i++){
        printf("%.2lf \n",customers1[i].finishTime-customers1[i].arrivalTime);
    }
    printf("\n");
    //finish of model 1
    //now I have to delete the vectors that I created with new in order to save memory
    //I found this deleting way in stackoverflow, they said it is efficient there so I hope it empties my memory.
    vector<Cashier>().swap(cashiers);
    vector<Customer>().swap(customers1);
    vector<Barista>().swap(baristas);
    //Start of model 2
    maxLengthCashierQ=0;
    double model2Finish=0;
    vector<Cashier> cashiers2=*new vector<Cashier>(cashierNumber);
    vector<Barista> baristas2=*new vector<Barista>(baristaNumber);
    priority_queue<Customer, vector<Customer>, CompareArrivalTime> cashierQueue2;
    vector<priority_queue<Customer, vector<Customer>, ComparePrice>> baristaQueues=*new vector<priority_queue<Customer, vector<Customer>, ComparePrice>>(baristaNumber);
    vector<int> maxLengthBaristaQs=*new vector<int>(baristaNumber);
    for(int i=0;i<baristaNumber;i++){
        maxLengthBaristaQs[i]=0;
    }
    while(!timeline2.empty()) {
        Customer current = timeline2.top();
        timeline2.pop();
        if (current.position == 0) {
            //This part is the same with the model 1
            bool hasFoundCashier = false;
            for (int i = 0; i < cashierNumber; i++) {
                if (cashiers2[i].currentCustomer == nullptr) {
                    cashiers2[i].takeCustomer(current);
                    current.cashier = i;
                    timeline2.push(current);
                    hasFoundCashier = true;
                    break;
                }
            }
            if (!hasFoundCashier) {
                cashierQueue2.push(current);
                current.position = 1;
                if (cashierQueue2.size() > maxLengthCashierQ)
                    maxLengthCashierQ = cashierQueue2.size();
            }
        }else if(current.position==2){
            //In this part, the only think that differs from model 1 is that the barista queues for cashiers are determined.
            int cashierIndex=current.cashier;
            cashiers2[cashierIndex].giveCustomer();
            if(!cashierQueue2.empty()){
                Customer n=cashierQueue2.top();
                n.currentTime=current.currentTime;
                cashierQueue2.pop();
                cashiers2[cashierIndex].takeCustomer(n);
                n.cashier=cashierIndex;
                timeline2.push(n);
            }
            bool hasFoundBarista=(baristas2[cashierIndex/3].currentCustomer== nullptr);
            if(hasFoundBarista) {
                baristas2[cashierIndex/3].takeCustomer(current);
                current.barista = cashierIndex/3;
                timeline2.push(current);
            }else {
                baristaQueues[cashierIndex/3].push(current);
                current.position = 3;
                if (baristaQueues[cashierIndex/3].size() > maxLengthBaristaQs[cashierIndex/3])
                    maxLengthBaristaQs[cashierIndex/3] = baristaQueues[cashierIndex/3].size();
            }
        }else if(current.position==4) {
            //This part is the same as model 1
            int baristaIndex = current.barista;
            baristas2[baristaIndex].giveCustomer();
            customers2[current.index].finishTime = current.currentTime;
            model2Finish = current.currentTime;
            if (!baristaQueues[baristaIndex].empty()) {
                Customer n = baristaQueues[baristaIndex].top();
                n.currentTime = current.currentTime;
                baristaQueues[baristaIndex].pop();
                baristas2[baristaIndex].takeCustomer(n);
                n.barista = baristaIndex;
                timeline2.push(n);
            }
        }
    }
    printf("%.2lf \n",model2Finish);
    printf("%d \n",maxLengthCashierQ);
    for(int i=0;i<cashierNumber/3;i++){
        printf("%d \n",maxLengthBaristaQs[i]);
    }
    for(int i=0;i<cashierNumber;i++){
        printf("%.2lf \n",cashiers2[i].totalWorkTime/model2Finish);
    }
    for(int i=0;i<baristaNumber;i++){
        printf("%.2lf \n",baristas2[i].totalWorkTime/model2Finish);
    }
    for(int i=0;i<customerNumber;i++){
        printf("%.2lf \n",customers2[i].finishTime-customers2[i].arrivalTime);
    }
    //model 2 is finished. Now let's free the memory that we use.
    vector<Cashier>().swap(cashiers2);
    vector<Customer>().swap(customers2);
    vector<Barista>().swap(baristas2);
    vector<priority_queue<Customer, vector<Customer>, ComparePrice>>().swap(baristaQueues);
    vector<int>().swap(maxLengthBaristaQs);
    

}
