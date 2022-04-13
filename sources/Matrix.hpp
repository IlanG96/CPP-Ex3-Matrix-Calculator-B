#include<iostream>
#include<vector>
namespace zich{
class Matrix
{
private:
    std::vector<std::vector<double>> _mat;
    int _row;
    int _col;
public:
    /**
     * @brief Gettets ans Setters
     * 
     */
    int getrow ()const{return _row;}
    int getcol()const{return _col;}
    int Sum_of_mat()const;
    std::vector<std::vector<double>> getmatrix(){return _mat;}
    void setrow(int r){this->_row=r;}
    void setcol(int c){this->_col=c;}
    //*******************************************************
    /**
     * @brief Construct a new Matrix object
     * 
     */
    Matrix(){}
    Matrix(std::vector<double> user_vec,int row,int col);
    //*******************************************************

    /**
     * @brief  "+" "-" "*" "*=" "+=" "-="
     */
    Matrix operator+ (Matrix const &other)const;
    Matrix operator- (Matrix const &other)const;
    Matrix &operator+= (Matrix const &other);
    Matrix &operator-= (Matrix const &other);
    Matrix operator*(const Matrix &other)const;
    Matrix operator*(double const scalar)const;
    Matrix &operator*= (double const scalar);
    Matrix &operator*=(const Matrix &other);
    //*******************************************************
    /**
     * @brief Increament operators
     */
    Matrix &operator++ (); //pre
    Matrix operator++ (int); //post
    Matrix &operator+ ();
    Matrix &operator- ();
    Matrix &operator-- (); //pre
    Matrix operator-- (int); //post
    //*******************************************************
    /**
     * @brief Boolean operators
     */
    //bool operator==(const Matrix &other)const;
    bool operator<=(const Matrix &other)const;
    bool operator>=(const Matrix &other)const;
    //bool operator!=(const Matrix &other)const;
    bool operator<(const Matrix &other)const;
    bool operator>(const Matrix &other)const;
    //*******************************************************
    friend Matrix operator*(const double scalar,const Matrix &other);
    friend bool operator==(const Matrix &mat1,const Matrix &mat2);
    friend bool operator!=(const Matrix &mat1,const Matrix &mat2);
    friend std::ostream &operator<<(std::ostream &COUT, const Matrix& a);
    friend std::istream &operator>>(std::istream &CIN, Matrix& a);
};

}