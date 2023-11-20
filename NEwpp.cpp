#include <iostream>
#include <thread>
#include <semaphore>
#include <syncstream>
#include<barrier>
#include<chrono>
#include <fstream>
using namespace std;
std::binary_semaphore sem_a(0);
std::binary_semaphore sem_b(0);
std::binary_semaphore sem_c(0);
std::binary_semaphore sem_d(0);
std::binary_semaphore sem_e(0);
std::binary_semaphore sem_f(0);
std::binary_semaphore sem_g(0);
std::binary_semaphore sem_h(0);
std::binary_semaphore sem_i(0);
std::binary_semaphore sem_j(0);
std::barrier limit_barrier(6); // Максимум 5 потоків + головний потік

void execute_action(std::osyncstream& sync_cout, std::binary_semaphore& sem, const char* action_name, int n) {
   
    {
    
        std::osyncstream(std::cout) << "Started list of actions " << action_name << std::endl;
        for (int i = 1; i <= n; i++) {
            std::osyncstream(std::cout) <<"Action " << i <<" of list "  << action_name  << endl;
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        std::osyncstream(std::cout) << "Finished list of actions " << action_name << std::endl;
        sem.release();
    }
    

}

void thread_a() {
    std::osyncstream sync_cout(std::cout);
    execute_action(sync_cout, sem_a, "a",8);
}

void thread_b() {
    std::osyncstream sync_cout(std::cout);
    execute_action(sync_cout, sem_b, "b",5);
}

void thread_c() {
    std::osyncstream sync_cout(std::cout);
    sem_a.acquire();
    sem_a.release();
    execute_action(sync_cout, sem_c, "c",9);
   
}

void thread_d() {
    std::osyncstream sync_cout(std::cout);
    sem_a.acquire();
    sem_a.release();
    execute_action(sync_cout, sem_d, "d",4);
   
}

void thread_e() {
    std::osyncstream sync_cout(std::cout);
    sem_b.acquire();
    sem_b.release();
    execute_action(sync_cout, sem_e, "e",6);
 
}

void thread_f() {
    std::osyncstream sync_cout(std::cout);
    sem_b.acquire();
    sem_b.release();
    execute_action(sync_cout, sem_f, "f",5);
   
}

void thread_g() {
    std::osyncstream sync_cout(std::cout);
    sem_c.acquire();
    execute_action(sync_cout, sem_g, "g",5);
    
}

void thread_h() {
    std::osyncstream sync_cout(std::cout);
    sem_d.acquire();
    sem_e.acquire();
    execute_action(sync_cout, sem_h, "h",6);
}

void thread_i() {
    std::osyncstream sync_cout(std::cout);
    sem_f.acquire();
    execute_action(sync_cout, sem_i, "i",7);
    
}

void thread_j() {
    std::osyncstream sync_cout(std::cout);
    sem_h.acquire();
    sem_i.acquire();
    sem_g.acquire();
    execute_action(sync_cout, sem_j, "j",4);
}
void threadFuncfirst() {
    thread_a(); thread_c(); thread_g(); thread_j();
}

void threadFuncSecond() {
    thread_b();
    thread_f();
    thread_i();
}
void threadFuncThird() {
    thread_d();
    thread_h();
}
int main() {
   // std::ofstream file("results.txt");
   // std::streambuf* coutbuf = std::cout.rdbuf(); 
 //   std::cout.rdbuf(file.rdbuf()); 

    std::thread thread_first(threadFuncfirst);
    std::thread thread_second(threadFuncSecond);

    std::thread thread_third(threadFuncThird);
    std::thread thread_fourth(thread_e);



   

    thread_first.join();
    thread_second.join();
    thread_third.join();
    thread_fourth.join();
  
  //  std::cout.rdbuf(coutbuf);
   return 0;
}
