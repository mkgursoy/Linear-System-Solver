/*
    Author: Matkap (prefix_sum)
*/

#include <bits/stdc++.h>

#define int long long

struct Fraction
{
    int Numerator, Denominator;
    Fraction()
    {
        Numerator = 0, Denominator = 0;
    }
    Fraction(int x)
    {
        Numerator = x, Denominator = 1;
    }
    Fraction(int x,int y)
    {
        Numerator = x, Denominator = y;
    }
    void stabilize()
    {
        if(Numerator <= 0 && Denominator <= 0)
        {
            Numerator *= -1;
            Denominator *= -1;
        }
        else if(Denominator <= 0)
        {
            Numerator *= -1;
            Denominator *= -1;
        }
        int gc = std::gcd(Numerator, Denominator);
        Numerator /= gc;
        Denominator /= gc;
    }
    void outp()
    {
        std::cout << Numerator << "/" << Denominator;
    }
    Fraction reciprocal()
    {
        return Fraction(Denominator, Numerator);
    }
    Fraction nega()
    {
        return Fraction(-Numerator, Denominator);
    }
    Fraction stable(Fraction x)
    {
        x.stabilize();
        return x;
    }
    Fraction operator+(const Fraction &other)
    {
        return Fraction(stable(Fraction(other.Denominator * Numerator + other.Numerator * Denominator, Denominator * other.Denominator)));
    }
    Fraction operator*(const Fraction &other)
    {
        return Fraction(stable(Fraction(Numerator * other.Numerator, Denominator * other.Denominator)));
    }
    Fraction operator/(const Fraction &other)
    {
        return Fraction(stable(Fraction(other.Denominator * Numerator, Denominator * other.Numerator)));
    }
};
const int mxN = 10000;
std::vector<Fraction> augmented_matrix[mxN];
void Interchange_Rows(int row_id1,int row_id2)
{
    swap(augmented_matrix[row_id1], augmented_matrix[row_id2]);
}
void Multiply_Row_By_Constant(Fraction Constant,int row_id)
{
    for(auto& it : augmented_matrix[row_id])
    {
        it = it * Constant;
    }
}
void Add_Row_To_Another(Fraction Constant,int row_id_add,int row_id_add_to)
{
    for(int K = 0;augmented_matrix[row_id_add_to].size() > K;K++)
    {
        augmented_matrix[row_id_add_to][K] = Constant * augmented_matrix[row_id_add][K] + augmented_matrix[row_id_add_to][K];
    }
}
bool Check_Row_For_Inconsistency(int i)
{
    bool t = false;
    for(int j = 0;(int)augmented_matrix[i].size() - 1 > j;j++)
    {
        if(augmented_matrix[i][j].Numerator != 0)
        {
            t = true;
            break;
        }
    }
    if(!t && augmented_matrix[i].back().Numerator != 0) return false;
    return true;
}
void solveLinearSystem()
{
    int numberOfEquations,numberOfVariables;
    std::cin >> numberOfEquations >> numberOfVariables;
    
    for(int i = 0;numberOfEquations > i;i++)
    {
        augmented_matrix[i].resize(numberOfVariables + 1);
        for(int j = 0;numberOfVariables >= j;j++)
        {
            int coefficient;
            std::cin >> coefficient;
            augmented_matrix[i][j] = Fraction(coefficient);
        }
    }
    int cur = 0;
    for(int j = 0;numberOfVariables > j;j++)
    {
        for(int i = cur;numberOfEquations > i;i++)
        {
            if(augmented_matrix[i][j].Numerator != 0)
            {
                Interchange_Rows(cur, i);
                break;
            }
        }
        if(augmented_matrix[cur][j].Numerator == 0) continue;
        Multiply_Row_By_Constant(augmented_matrix[cur][j].reciprocal(), cur);
        for(int i = cur + 1;numberOfEquations > i;i++)
        {
            Add_Row_To_Another(augmented_matrix[i][j].nega(), cur, i);
        }
        cur++;
    }
    std::cout << "A Possible Row Echelon Form: " << std::endl;
    for(int i = 0;numberOfEquations > i;i++)
    {
        for(int j = 0;numberOfVariables >= j;j++)
        {
            augmented_matrix[i][j].outp();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    for(int j = 0;numberOfVariables > j;j++)
    {
        int cc = -1;
        for(int i = numberOfEquations - 1;i >= 0;i--)
        {
            if(augmented_matrix[i][j].Numerator == 1)
            {
                cc = i;
                break;
            }
        }
        if(cc == -1) continue;
        for(int i = 0;cc > i;i++)
        {
            Add_Row_To_Another(augmented_matrix[i][j].nega(), cc, i);
        }
    }
    std::cout << "Reduced Row Echelon Form: " << std::endl;
    for(int i = 0;numberOfEquations > i;i++)
    {
        for(int j = 0;numberOfVariables >= j;j++)
        {
            augmented_matrix[i][j].outp();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    for(int i = 0;numberOfEquations > i;i++)
    {
        if(!Check_Row_For_Inconsistency(i))
        {
            std::cout << "There Exist 0 Solutions!" << std::endl;
            return;
        }
    }
    std::vector<int> leading;
    std::vector<int> free;
    for(int i = 0;numberOfEquations > i;i++)
    {
        bool found_leading = false;
        for(int j = 0;numberOfVariables > j;j++)
        {
            if(augmented_matrix[i][j].Numerator == 1 && !found_leading)
            {
                leading.push_back(j);
                found_leading = true;
                continue;
            }
        }
    }
    int ind = 0;
    for(int i = 0;numberOfVariables > i;i++)
    {
        if((int)leading.size() <= ind || leading[ind] != i)
        {
            free.push_back(i);
        }
        else ind++;
    }
    //Free Variables Will Be Set To 0
    std::vector<Fraction> val(numberOfVariables);
    for(auto i : free) val[i] = Fraction(0);
    for(int i = 0;numberOfEquations > i;i++)
    {
        for(int j = 0;numberOfVariables > j;j++)
        {
            if(augmented_matrix[i][j].Numerator == 1)
            {
                val[j] = augmented_matrix[i][numberOfVariables];
                for(int k = j + 1;numberOfVariables > k;k++)
                {
                    if(augmented_matrix[i][k].Numerator != 0)
                    {
                        val[j] = val[j] + val[k] * augmented_matrix[i][k].nega();
                    }
                }
                break;
            }
        }
    }
    if(!free.size()) std::cout << "There Exist 1 Solution!" << std::endl;
    else std::cout << "There Exist Infinite Solutions!" << std::endl;
    std::cout << "Possible Solution: " << std::endl;
    for(int i = 0;numberOfVariables > i;i++)
    {
        val[i].outp();
        std::cout << " ";
    }
    std::cout << std::endl;
}
int32_t main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solveLinearSystem();
}