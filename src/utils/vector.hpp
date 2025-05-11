#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdlib>
#include <string>
#include <iostream>


#include <stdexcept>

#define INIT_MAX_SIZE 10

template<typename T>
class Vector{
    private:
        unsigned int size;
        unsigned int maxSize;

        T** arr;

        void Free(){
            if (arr){
                for (unsigned int i = 0; i < size; ++i){
                    delete arr[i];
                }
                delete[] arr;
            }
            size = 0;
            maxSize = 0;
            arr = nullptr;
        }

        // Realloc if arr != nullptr
        void Alloc(int addedSize){
            T** temp =  new T*[maxSize + addedSize];
            
            if (arr){
                for (unsigned int i = 0; i < size; i++){
                    temp[i] = arr[i];
                }
                Free();
            }
            arr = temp;
            
            size = size;
            maxSize = maxSize + addedSize;
        }

    public:
        Vector() : size{0}, maxSize{0}, arr{nullptr}{
            Alloc(INIT_MAX_SIZE);
        }
        Vector(Vector<T> const& vec){
            arr = nullptr;
            Alloc(vec.maxSize);
            size = vec.size;
            maxSize = vec.maxSize;
            
            for (unsigned int i = 0; i < vec.size; ++i){
                arr[i] = vec.arr[i];
            }
        }
        Vector(Vector<T> &&vec){
            arr = vec.arr;
            size = vec.size;
            maxSize = vec.maxSize;

            vec.arr = nullptr;
            vec.size = 0;
            vec.maxSize = 0;
        }

        ~Vector(){
            Free();
        }

        const Vector<T>& operator=(const Vector<T> &vec){
            if (this == &vec) return *this;
            
            if (arr) Free();
            Alloc(vec.maxSize);
            size = vec.size;
            maxSize = vec.maxSize;

            for (unsigned int i = 0; i < vec.size; ++i){
                arr[i] = vec.arr[i];
            }
            return *this;
        }
        const Vector<T>& operator=(Vector<T> &&vec){
            if (this == &vec) return *this;

            if (arr) Free();
            arr = vec.arr;
            size = vec.size;
            maxSize = vec.maxSize;

            vec.arr = nullptr;
            vec.size = 0;
            vec.maxSize = 0;
        }

        T& operator[](unsigned int pos) const{
            if (pos >= size) throw std::out_of_range("Out of range : index = " + std::to_string(pos));
            return *(arr[pos]);
        }

        template<typename G>
        void Push_back(G &obj){
            if (!arr) Alloc(INIT_MAX_SIZE);

            G* newObj = new G{obj};
            if (size == maxSize) Alloc(INIT_MAX_SIZE);
            arr[size++] = (T*) newObj;
        }

        template<typename G>
        void Push_back(G obj){
            if (!arr) Alloc(INIT_MAX_SIZE);

            G* newObj = new G{obj};
            if (size == maxSize) Alloc(INIT_MAX_SIZE);
            arr[size++] = (T*) newObj;
        }

        T const& Pop_back(){
            if (size <= 0) throw std::length_error("No more element to remove");
            --size;
            T obj{*arr[size]};
            delete arr[size];
            return obj;
        }

        void Erase(unsigned int pos){
            if (pos >= size) throw std::out_of_range("Out of range : index = " + std::to_string(pos));
            delete arr[pos];
            for (unsigned int i = pos; i < size-1; ++i){
                arr[i] = arr[i+1];
            }
            --size;
        }

        void Clear(){
            Free();
            Alloc(INIT_MAX_SIZE);
        }


        unsigned int Size() { return size; }

};

#endif