/**
 * @file Matrix.cpp
 * @author Ilan Gold (goldlmilan@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
#include<vector>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include "Matrix.hpp"
using namespace std;


vector<string> split_at( const string &delimiter, const string &str);
/**
 * @brief Exceptions function
 * 
 */
void Inputcheck(int vecsize,int row,int col){
    if (vecsize!=row*col)
    {
        throw runtime_error("ERR: The row and col enterd to the constructor are not the same as the matrix size");  
    }
    if (row<=0 || col<=0)
    {
    throw runtime_error("ERR: Matrix cant be with negetive sizes");  
    }
      
}
void dimensions_check(int row1,int col1,int row2,int col2){
    if (row1<=0||row2<=0||col1<=0||col2<=0)
    {
        throw runtime_error("ERR: Matrix cant be with negetive sizes");
    }
    if (row1!=row2||col1!=col2)
    {
        throw runtime_error("ERR: This 2 matrices unequal dimensions");
    }
    
}


namespace zich{
    /**
     * @brief Construct a new Matrix object
     * 
     * @param user_vec -matrix values
     * @param row 
     * @param col 
     */
Matrix::Matrix(vector<double> user_vec,int row,int col){
    Inputcheck(user_vec.size(),row,col);
    this->_col=col;
    this->_row=row;
    vector<double> curr_row;
    int end_row_counter=0;
    for (unsigned long j = 0; j < row*col; j++){

        curr_row.push_back(user_vec.at(j));
        end_row_counter++;
        if (end_row_counter==col){
            this->_mat.push_back(curr_row);
            end_row_counter=0;
            curr_row.resize(0);
        }    
    }
}
/*******************************************************/
 
/**
 * @brief "+" "-" "*" "++" "--" operators
 * 
 */
    Matrix Matrix::operator+ (Matrix const &other)const{
        dimensions_check(this->getrow(),this->getcol(),other.getrow(),other.getcol());
        std::vector<double> newVec;
        for (unsigned long i = 0; i < this->getrow(); i++)
        {
           for (unsigned long j = 0; j < this->getcol(); j++)
           {
              newVec.push_back(this->_mat.at(i).at(j)+other._mat.at(i).at(j));
           }
        }
        return Matrix(newVec,this->getrow(),this->getcol());
    }

        Matrix Matrix::operator- (Matrix const &other)const{
        dimensions_check(this->getrow(),this->getcol(),other.getrow(),other.getcol());
        std::vector<double> newVec;
        for (uint i = 0; i < _row; i++)
        {
           for (uint j = 0; j < _col; j++)
           {
               newVec.push_back(this->_mat.at(i).at(j)-other._mat.at(i).at(j));
           }
        }
        return Matrix(newVec,this->getrow(),this->getcol());
    }

    Matrix Matrix::operator*(const Matrix &other)const{
        if (this->getcol()!=other.getrow())
        {
            throw runtime_error("ERR: This 2 matrices unequal dimensions for multiplication");
        }
        std::vector<double> newVec;
        for (uint i = 0; i < this->getrow(); i++)
        {
            for (uint j = 0; j < other.getcol(); j++)
            {
                double sum=0;
                for (uint k = 0; k < other.getrow(); k++)
                {
                    sum+=this->_mat.at(i).at(k)*other._mat.at(k).at(j);

                }
                newVec.push_back(sum);
            }
        }
        return Matrix(newVec,this->getrow(),other.getcol());
    }

    Matrix Matrix::operator*(double const scalar)const{
        std::vector<double> newVec;
        for (uint i = 0; i < this->getrow(); i++)
        {
            for (uint j = 0; j < this->getcol(); j++)
            {
                newVec.push_back(this->_mat.at(i).at(j)*scalar);
            }
        }
        return Matrix(newVec,this->getrow(),this->getcol());
    }



    Matrix &Matrix::operator-- (){
        for (uint i = 0; i < _row; i++)
        {
            for (uint j = 0; j < _col; j++)
            {
               this->_mat.at(i).at(j)--;
            }
            
        }
        return *this;
    }

    Matrix Matrix::operator-- (int){
        Matrix new_mat=*this;
        --(*this);
        return new_mat;
        } 

        //pre ++mat
        Matrix &Matrix::operator++ () {
        for (size_t i = 0; i < _row; i++)
        {
            for (size_t j = 0; j < _col; j++)
            {
                this->_mat.at(i).at(j)++;
            }
            
        }
        return *this;
    }
    
    //post mat++
    Matrix Matrix::operator++ (int){
        Matrix new_mat=*this;
        ++(*this);
        return new_mat;
        } 

    //*******************************************************************

    /**
     * @brief "+=" "-+" "*=" operators
     */
    Matrix &Matrix::operator+=(Matrix const &other){
        *this=*this+other;
        return *this;
    }

    Matrix &Matrix::operator-=(Matrix const &other){
        *this=*this-other;
        return *this;
    }

    Matrix &Matrix::operator*=(double const scalar){
        for (uint i = 0; i < this->getrow(); i++)
        {
            for (uint j = 0; j < this->getcol(); j++)
            {
                this->_mat.at(i).at(j)*=scalar;
            }
            
        }
        return *this;
        }
    
    Matrix &Matrix::operator*=(const Matrix &other){
        *this=*this*other;
        return *this;
        }

    //*******************************************************************

    Matrix &Matrix::operator- (){      
        return *this*=-1;
    }

    
    Matrix &Matrix::operator+ (){
        return *this;
    }

    //*******************************************************************
    
/**
 * @brief  boolean comparison operators
 */

    // bool Matrix::operator==(const Matrix &other)const{
    //     dimensions_check(this->getrow(),this->getcol(),other.getrow(),other.getcol());
    //     for (uint i = 0; i < this->getrow(); i++)
    //     {
    //         for (uint j = 0; j < this->getcol(); j++)
    //         {
    //             if (this->_mat.at(i).at(j)!=other._mat.at(i).at(j))
    //             {
    //                return false;
    //             }
                
    //         }
            
    //     }
        
    //     return true;
    // }


    bool Matrix::operator<=(const Matrix &other)const{
        dimensions_check(this->getrow(),this->getcol(),other.getrow(),other.getcol());      
        int mat_sum1=this->Sum_of_mat();
        int mat_sum2=other.Sum_of_mat();
        return mat_sum1<=mat_sum2;
    }
    bool Matrix::operator>=(const Matrix &other)const{
        dimensions_check(this->getrow(),this->getcol(),other.getrow(),other.getcol());        
        int mat_sum1=this->Sum_of_mat();
        int mat_sum2=other.Sum_of_mat();
        return mat_sum1>=mat_sum2;
    }
    bool Matrix::operator>(const Matrix &other)const{
        dimensions_check(this->getrow(),this->getcol(),other.getrow(),other.getcol());      
        int mat_sum1=this->Sum_of_mat();
        int mat_sum2=other.Sum_of_mat();
        return mat_sum1>mat_sum2;
    }
    bool Matrix::operator<(const Matrix &other)const{
        dimensions_check(this->getrow(),this->getcol(),other.getrow(),other.getcol());     
        int mat_sum1=this->Sum_of_mat();
        int mat_sum2=other.Sum_of_mat();
        return mat_sum1<mat_sum2;
    }

    // bool Matrix::operator!=(const Matrix &other)const{
    //     for (uint i = 0; i < this->getrow(); i++)
    //     {
    //         for (uint j = 0; j < this->getcol(); j++)
    //         {
    //             if (this->_mat.at(i).at(j)==other._mat.at(i).at(j))
    //             {
    //                return false;
    //             }
                
    //         }
            
    //     }
        
    //     return true;
    // }
    //*******************************************************************


/**
 * @brief friend functions implementation
 */
    bool operator==(const Matrix &mat1,const Matrix &mat2){
        dimensions_check(mat1.getrow(),mat1.getcol(),mat2.getrow(),mat2.getcol());
        for (uint i = 0; i < mat1.getrow(); i++)
        {
            for (uint j = 0; j < mat1.getcol(); j++)
            {
                if (mat1._mat.at(i).at(j)!=mat2._mat.at(i).at(j))
                {
                   return false;
                }
                
            }
        }
        return true;
    }

   bool operator!=(const Matrix &mat1,const Matrix &mat2){
        return !(mat1 == mat2);
    }

    ostream &operator<<(ostream &COUT, const Matrix& a){
        for (uint i = 0; i < a.getrow(); i++)
        {
            COUT<<"[";
            for (uint j = 0; j < a.getcol(); j++)
            {
               COUT<<a._mat.at(i).at(j);
               if (j!=a.getcol()-1)
               {
                    COUT<<" ";
               }
            }
            COUT<<"]";
            if (i!=a.getrow()-1)
            {
                COUT<<"\n";
            }
        } 
        return COUT;
    }

    istream &operator>>(istream &CIN, Matrix& a){
        string line;
        string text;
        string mat_nums;
        std::vector<double> newVec;
        int rows=1;
        int col=0;
        while(getline(CIN,line)){
            text+=line;
        }
        for (uint i = 0; i < text.length()-1; i++)
        {
            if ((text.at(i)==']' && text.at(i+1)!=',')|| (text.at(i)=='[' && text.at(i+1)==' '))
            {
                throw invalid_argument("ERR: check the '[' and ']' you entered");
            }  
            if (text.at(i)==',' && text.at(i+1)!=' ')
            {
                throw invalid_argument("There's a ',' without space after it in you string");
            }
            if (text.at(i)==']')
            {
                rows++;
            }
            if (text.at(i)!=']'&&text.at(i)!='[')
            {
                mat_nums+=text.at(i);
            }  
        }
        vector<string> num_rows= split_at(",",mat_nums);        
        col=int(num_rows.size());
        mat_nums.clear();
        line.clear();
        for (uint i = 0; i < num_rows.size(); i++)
        {
            for (uint j = 0; j < num_rows.at(i).size()-1; j++)
            {
                if (num_rows.at(i).at(j+1) == ' '||num_rows.at(i).at(j+1) == '\n')
                {
                    line+=num_rows.at(i).at(j);
                    cout<<line<<endl;
                    newVec.push_back(stoi(line));
                    line.clear();
                    
                }
                else{
                    line+=num_rows.at(i).at(j);
                } 
            }
        }
        a=Matrix(newVec,rows,col);   
        return CIN;
    }

    Matrix operator*(const double scalar,const Matrix &other) {
        std::vector<double> newVec;
        for (uint i = 0; i < other.getrow(); i++)
        {
            for (uint j = 0; j < other.getcol(); j++)
            {
                newVec.push_back(other._mat.at(i).at(j)*scalar);
            }
            
        }
        return Matrix(newVec,other.getrow(),other.getcol());
    }

/**
 * @brief Function that sum all the values in the matrix
 * 
 * @return sum 
 */
    int Matrix::Sum_of_mat() const{
        int sum=0;
        for (uint i = 0; i < this->getrow(); i++)
        {
            for (uint j = 0; j < this->getcol(); j++)
            {
                sum+=this->_mat.at(i).at(j);
            }
            
        }
        return sum;
    }

}
/**
 * @brief Function that split the contents of a string into a vector array at a given parameter.
 * 
 * @param delimiter 
 * @param str 
 * @return vector<string> 
 */
vector<string> split_at( const string &delimiter, const string &str)
{
    vector<string> arr;

    int strleng = str.length();
    uint delleng = delimiter.length();
    if (delleng==0){
        return arr;}//no change

    uint i=0;
    uint k=0;
    while( i<strleng )
    {
        uint j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j]){
            j++;
        }
        if (j==delleng)//found delimiter
        {
            arr.push_back(str.substr(k, i-k) );
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    arr.push_back(  str.substr(k, i-k) );
    return arr;
}


/**
 * @brief Main for testing
 * 
 */
// int main(){
// //     vector<double> vectorA = {1, 2, 3, 4,
// //                               5, 6, 7, 8,
// //                               9,10,11,12};
// //     vector<double> vectorB = {1, 2, 3,
// //                               4, 5, 6,
// //                               7, 8, 9,
// //                               10,11,12};
// //     //A*B==C
// //     vector<double> vectorC = {70, 80, 90,
// //                               158, 184, 210,
// //                               246, 288, 330};
// //     //B*A=D
// //     vector<double > vectorD={38,44,50,56,
// //                              83,98,113,128,
// //                              128,152,176,200,
// //                              173,206,239,272};
// //     vector<double> vectorI_3={1,0,0,
// //                               0,1,0,
// //                               0,0,1};
// //     vector<double> vectorI_4={1,0,0,0,
// //                               0,1,0,0,
// //                               0,0,1,0,
// //                               0,0,0,1};
// //     vector<double > vector_zero_3={0,0,0,
// //                                    0,0,0,
// //                                    0,0,0};
// //     vector<double > vector_zero_4={0,0,0,0,
// //                                    0,0,0,0,
// //                                    0,0,0,0,
// //                                    0,0,0,0};
// //     vector<double> vector_one_3={1,1,1,
// //                                  1,1,1,
// //                                  1,1,1};
// //     vector<double> vector_one_4={1,1,1,1,
// //                                  1,1,1,1,
// //                                  1,1,1,1,
// //                                  1,1,1,1};


// //     zich::Matrix A{vectorA, 3, 4};
// //     zich::Matrix B{vectorB, 4, 3};
// //     zich::Matrix C{vectorC,3,3};
// //     zich::Matrix D{vectorD,4,4};
// //     zich::Matrix I_3{vectorI_3,3,3};
// //     zich::Matrix I_4{vectorI_4,4,4};
// //     zich::Matrix zero_3{vector_zero_3,3,3};
// //     zich::Matrix zero_4{vector_zero_4,4,4};
// //     zich::Matrix oneMatrix_3{vector_one_3,3,3};
// //     zich::Matrix oneMatrix_4{vector_one_4,4,4};
// //     cout << zero_3 <<endl;
// //     cout << zero_4 <<endl;
// //     zero_3++;
// //     ++zero_4;
// //     cout << zero_3 <<endl;
// //     cout << zero_4 <<endl;
//     std::vector<double> unit_matrix = {1, 0, 0, 0, 1, 0, 0, 0, 1};
//     zich::Matrix mat1{unit_matrix,3,3};
//     istringstream is7{"[1 1 1 1], [1 1 1 1], [1 1 1 1]\n"};
//     is7 >> mat1;
//      return 0;
//  }