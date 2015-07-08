#include<utility>

template<typename T>
class SmartPtr {
    template<typename S>
    friend class SmartPtr;

public:
    SmartPtr() : m_p(nullptr), m_num(nullptr) {}

    SmartPtr(T* p) : m_p(p), m_num(nullptr) {
        if (m_p != nullptr) {
            m_num = new int(1);
        }
    }

    SmartPtr(SmartPtr& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        incCounter();
    }

    template<typename T1>
    SmartPtr(SmartPtr<T1> const& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        incCounter();
    }

    SmartPtr(SmartPtr&& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        ptr.clearReferences();
    }

    template<typename T1>
    SmartPtr(SmartPtr<T1>&& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        ptr.clearReferences();
    }

    SmartPtr& operator=(SmartPtr const& ptr) {
        if(&ptr == this) return *this;
        copy(ptr);
        return *this;
    }

    template<typename T1>
    SmartPtr& operator=(SmartPtr<T1> const& ptr) {
        copy(ptr);
        return *this;
    }

    SmartPtr& operator=(SmartPtr&& ptr) {
        if(&ptr == this) return *this;
        move(std::move(ptr));
        return *this;
    }

    template<typename T1>
    SmartPtr& operator=(SmartPtr<T1>&& ptr) {
        move(std::move(ptr));
        return *this;
    }

    ~SmartPtr() { release(); }

    T& operator*() { return *m_p; }

    T const& operator*() const { return *m_p; }

    T* operator->() { return m_p; }

    T const* operator->() const { return m_p; }

    int use_count() const { return *m_num; }

    T* get() { return m_p; }

    T const* get() const { return m_p; }

private:
    void incCounter() {
        if (m_num != nullptr) {
            ++*m_num;
        }
    }

    void clearReferences() {
        m_p = nullptr;
        m_num = nullptr;
    }

    void release() {
        if (m_num != nullptr && --*m_num == 0) {
            delete m_p;
            delete m_num;
        }
        clearReferences();
    }

    template<typename T1>
    void move(SmartPtr<T1>&& ptr) {
        release();
        m_p = ptr.m_p;
        m_num = ptr.m_num;
        ptr.clearReferences();
    }

    template<typename T1>
    void copy(SmartPtr<T1> const& ptr) {
        release();
        m_p = ptr.m_p;
        m_num = ptr.m_num;
        if (m_num != nullptr) {
            ++*m_num;
        }
    }

    T* m_p;
    int* m_num;
};

template<typename T, typename ... Args>
SmartPtr<T> makeSmartPtr(Args&& ... args) {
    return SmartPtr<T>(new T(std::forward<Args>(args)...));
}


template<typename T>
class SmartPtr<T[]> {
    template<typename S>
    friend class SmartPtr;

public:
    SmartPtr() : m_p(nullptr), m_num(nullptr) {}

    SmartPtr(T* p) : m_p(p), m_num(nullptr) {
        if (m_p != nullptr) {
            m_num = new int(1);
        }
    }

    SmartPtr(SmartPtr& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        incCounter();
    }

    template<typename T1>
    SmartPtr(SmartPtr<T1[]> const& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        incCounter();
    }

    SmartPtr(SmartPtr&& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        ptr.clearReferences();
    }

    template<typename T1>
    SmartPtr(SmartPtr<T1[]>&& ptr) : m_p(ptr.m_p), m_num(ptr.m_num) {
        ptr.clearReferences();
    }

    SmartPtr& operator=(SmartPtr const& ptr) {
        if(&ptr == this) return *this;
        copy(ptr);
        return *this;
    }

    template<typename T1>
    SmartPtr& operator=(SmartPtr<T1[]> const& ptr) {
        copy(ptr);
        return *this;
    }

    SmartPtr& operator=(SmartPtr&& ptr) {
        if(&ptr == this) return *this;
        move(std::move(ptr));
        return *this;
    }

    template<typename T1>
    SmartPtr& operator=(SmartPtr<T1[]>&& ptr) {
        move(std::move(ptr));
        return *this;
    }

    ~SmartPtr() { release(); }

    T& operator*() { return *m_p; }

    T const& operator*() const { return *m_p; }

    T* operator->() { return m_p; }

    T const* operator->() const { return m_p; }

    int use_count() const { return *m_num; }

    T* get() { return m_p; }

    T const* get() const { return m_p; }

    T& operator[](int i) { return m_p[i]; }

    T const& operator[](int i) const { return m_p[i]; }

private:
    void incCounter() {
        if (m_num != nullptr) {
            ++*m_num;
        }
    }

    void clearReferences() {
        m_p = nullptr;
        m_num = nullptr;
    }

    void release() {
        if (m_num != nullptr && --*m_num == 0) {
            delete[] m_p;
            delete m_num;
        }
        clearReferences();
    }

    template<typename T1>
    void move(SmartPtr<T1[]>&& ptr) {
        release();
        m_p = ptr.m_p;
        m_num = ptr.m_num;
        ptr.clearReferences();
    }

    template<typename T1>
    void copy(SmartPtr<T1[]> const& ptr) {
        release();
        m_p = ptr.m_p;
        m_num = ptr.m_num;
        if (m_num != nullptr) {
            ++*m_num;
        }
    }

    T* m_p;
    int* m_num;
};

