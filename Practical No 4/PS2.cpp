#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const int BUFFER_SIZE = 5;
int buffer[BUFFER_SIZE];
int count_items = 0;  // number of items in buffer
int in_pos = 0, out_pos = 0;

omp_lock_t lock_var;

void produce_item(int item) {
    buffer[in_pos] = item;
    in_pos = (in_pos + 1) % BUFFER_SIZE;
    count_items++;
}

int consume_item() {
    int item = buffer[out_pos];
    out_pos = (out_pos + 1) % BUFFER_SIZE;
    count_items--;
    return item;
}

int main() {
    omp_init_lock(&lock_var);

    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if (tid == 0) { // Producer
            for (int i = 1; i <= 10; i++) {
                bool produced = false;
                while (!produced) {
                    omp_set_lock(&lock_var);
                    if (count_items < BUFFER_SIZE) {
                        produce_item(i);
                        cout << "Producer produced: " << i << "\n";
                        produced = true;
                    }
                    omp_unset_lock(&lock_var);
                }
            }
        } else { // Consumer
            for (int i = 1; i <= 10; i++) {
                bool consumed = false;
                while (!consumed) {
                    omp_set_lock(&lock_var);
                    if (count_items > 0) {
                        int item = consume_item();
                        cout << "Consumer consumed: " << item << "\n";
                        consumed = true;
                    }
                    omp_unset_lock(&lock_var);
                }
            }
        }
    }

    omp_destroy_lock(&lock_var);
    return 0;
}
