/*
    Author: Matkap (prefix_sum)
*/

#include <bits/stdc++.h>

#define int long long

const int MOD = 1e9 + 7;

int mul(int a,int b,int mod = MOD)
{
    if(a > mod)
    a %= mod;
    if(b > mod)
    b %= mod;
    return a * 1LL * b % mod;
}
int sum(int a,int b,int mod = MOD)
{
    if(a > mod)
    a %= mod;
    if(b > mod)
    b %= mod;
    return (a + b + mod) % mod;
}
int binpow(int base,int power,int mod = MOD)
{
    if(power == 1) return base;
    if(power == 0) return 1;
    
    if(power%2==1)
    {
        int a;  
        a = binpow(base,(power - 1)/2);
        return mul(base, mul(a, a, mod), mod);
    } 
    else
    {
        int a;
        a = binpow(base,power/2);
        return mul(a, a, mod);
    } 
 
}
int inv(int a,int mod = MOD)
{
    if(a > mod)
    a %= mod;
    return binpow(a, mod - 2) % mod;
}
const int mxN = 607;
std::vector<int> augmented_matrix[mxN];
void Interchange_Rows(int row_id1,int row_id2)
{
    swap(augmented_matrix[row_id1], augmented_matrix[row_id2]);
}
void Multiply_Row_By_Constant(int Constant,int row_id)
{
    for(auto& it : augmented_matrix[row_id])
    {
        it = mul(it, Constant);
    }
}
void Add_Row_To_Another(int Constant,int row_id_add,int row_id_add_to)
{
    for(int K = 0;augmented_matrix[row_id_add_to].size() > K;K++)
    {
        augmented_matrix[row_id_add_to][K] = sum(mul(Constant, augmented_matrix[row_id_add][K]),augmented_matrix[row_id_add_to][K]);
    }
}
bool Check_Row_For_Inconsistency(int row_id)
{
    bool t = false;
    for(int j = 0;(int)augmented_matrix[row_id].size() > j + 1;j++)
    {
        if(augmented_matrix[row_id][j] != 0)
        {
            t = true;
            break;
        }
    }
    if(!t && augmented_matrix[row_id].back() != 0) return false;
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
            augmented_matrix[i][j] = coefficient;
        }
    }
    int cur = 0;
    for(int j = 0;numberOfVariables > j;j++)
    {
        if(cur == numberOfEquations) break;
        for(int i = cur;numberOfEquations > i;i++)
        {
            if(augmented_matrix[i][j] != 0)
            {
                Interchange_Rows(cur, i);
                break;
            }
        }
        if(augmented_matrix[cur][j] == 0) continue;
        Multiply_Row_By_Constant(inv(augmented_matrix[cur][j]), cur);
        for(int i = cur + 1;numberOfEquations > i;i++)
        {
            Add_Row_To_Another(-augmented_matrix[i][j], cur, i);
        }
        cur++;
    }
    std::cout << "A Possible Row Echelon Form: " << std::endl;
    for(int i = 0;numberOfEquations > i;i++)
    {
        for(int j = 0;numberOfVariables >= j;j++)
        {
            std::cout << augmented_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for(int j = 0;numberOfVariables > j;j++)
    {
        int cc = -1;
        for(int i = numberOfEquations - 1;i >= 0;i--)
        {
            if(augmented_matrix[i][j] == 1)
            {
                cc = i;
                break;
            }
        }
        if(cc == -1) continue;
        for(int i = 0;cc > i;i++)
        {
            Add_Row_To_Another(-augmented_matrix[i][j], cc, i);
        }
    }
    std::cout << "Reduced Row Echelon Form: " << std::endl;
    for(int i = 0;numberOfEquations > i;i++)
    {
        for(int j = 0;numberOfVariables >= j;j++)
        {
            std::cout << augmented_matrix[i][j] << " ";
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
            if((augmented_matrix[i][j] == 1) && !found_leading)
            {
                leading.push_back(j);
                found_leading = true;
                continue;
            }
        }
    }
    int tt = 0;
    for(int i = 0;numberOfVariables > i;i++)
    {
        if((int)leading.size() <= tt || leading[tt] != i)
        {
            free.push_back(i);
        }
        else tt++;
    }
    //Free Variables Will Be Set To 0
    std::vector<int> val(numberOfVariables);
    for(auto i : free) val[i] = 0;
    for(int i = 0;numberOfEquations > i;i++)
    {
        for(int j = 0;numberOfVariables > j;j++)
        {
            if(augmented_matrix[i][j] == 1)
            {
                val[j] = augmented_matrix[i][numberOfVariables];
                for(int k = j + 1;numberOfVariables > k;k++)
                {
                    if(augmented_matrix[i][k] != 0)
                    {
                        val[j] = sum(val[j], mul(val[k], -augmented_matrix[i][k]));
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
        std::cout << val[i] << " ";
    }
    std::cout << std::endl;
}
int32_t main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solveLinearSystem();
}