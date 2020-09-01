#pragma once
typedef struct{int data;} Type0;
typedef struct{int data;} Type1;
typedef struct{int data;} Type2;
typedef struct{int data;} Type3;
inline bool operator==(const Type0& lhs, const Type0& rhs){ return lhs.data == rhs.data;}
inline bool operator==(const Type1& lhs, const Type1& rhs){ return lhs.data == rhs.data;}
inline bool operator==(const Type2& lhs, const Type2& rhs){ return lhs.data == rhs.data;}
inline bool operator==(const Type3& lhs, const Type3& rhs){ return lhs.data == rhs.data;}
std::ostream& operator<< (std::ostream &os, const Type0& type){
  os << "Type0: " << type.data;
  return os;
}
std::ostream& operator<< (std::ostream &os, const Type1& type){
  os << "Type1: " << type.data;
  return os;
}
std::ostream& operator<< (std::ostream &os, const Type2& type){
  os << "Type2: " << type.data;
  return os;
}
std::ostream& operator<< (std::ostream &os, const Type3& type){
  os << "Type3: " << type.data;
  return os;
}
