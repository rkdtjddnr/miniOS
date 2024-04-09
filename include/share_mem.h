void* make_shm(const char* shm_name);
void unlink_shm(const char* shm_name);
void insert_chr_to_shm(void* ptr, const char* message);
void get_chr_from_shm(void* ptr);
void check_ptr(const char* type, void* ptr);
