namespace Singleton {
    template<typename T>
    class Singleton {
        public:
            Singleton<T>(const <T>&);
            Singleton<T>(T&& x);

            Singleton <T>(const Singleton<T>&) = delete;
            Singleton<T>& operator=(const Singleton<T>&) = delete;

            ~Singleton<T>();

        private:
            
    };
}