std::vector<Fork>; // Vector with 5 elements

std::mutex permission;

std::condition_variable_any cv;

int num_allowed = forks.size() - 1;

void wait_for_permission()
{
    permission.lock();

    cv.wait(permission, [this] { return numAllowed > 0; });

    num_allowed--;

    permission.unlock();
}

void grant_permission()
{
    permission.lock();

    num_allowed++;

    if (num_allowed == 1)
    {
        cv.notify_all();
    }
}

void think()
{
    // think
}

void eat()
{
    wait_for_permission();

    forks[id].mux.lock();
    forks[id + 1].mux.lock();

    think();

    forks[id].mux.unlock();
    forks[id + 1].mux.unlock();

    grant_permission();
}