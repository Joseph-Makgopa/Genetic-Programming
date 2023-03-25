#include <functional>
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <atomic>

class thread_pool{
public:
	using job = std::function<void()>;	
	~thread_pool();
	void set_num_threads(std::size_t num);
	void wait();
	void start();
	void stop() noexcept;
	void add_job(job task);
	static thread_pool& instance();
private:
	explicit thread_pool(std::size_t num_threads);
	std::size_t num_threads = 10;
	std::vector<std::thread> workers;
	std::condition_variable condition;
	std::mutex mutex_object;
	bool terminate = false;
	std::queue<job> jobs;
};