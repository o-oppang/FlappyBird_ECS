//
//  Singleton.h
//  EnTT_Pacman
//
//  Created by 심다은 on 29/09/2019.
//

#ifndef Singleton_h
#define Singleton_h

template <class T>
class Singleton
{
public:
    static T* Instance() {
        if(!m_pInstance) {
            m_bInitialized = true;
            m_pInstance = new T;
        }
        assert(m_pInstance !=NULL);
        return m_pInstance;
    }

    static void destroyInstance() {
        if (m_pInstance) {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    }

    static bool m_bInitialized;

protected:
     Singleton() {
         assert(!m_pInstance);
         assert(m_bInitialized);
     };
private:
    static T* m_pInstance;
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
};

template <class T> T* Singleton<T>::m_pInstance = NULL;
template <class T> bool Singleton<T>::m_bInitialized = false;

#endif /* Singleton_h */
