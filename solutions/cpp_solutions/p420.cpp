#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int strongPasswordChecker(string password)
    {
        // easy case - can always satisfy requirements with only additions if the pw is short enough
        if (password.size() <= 3)
            return 6 - password.size();

        bool digit{false}, upper{false}, lower{false};
        // number of times a character repeats
        vector<int> repeats;

        for (size_t i{0}, j; i < password.size(); i = j)
        {
            digit = digit || isdigit(password[i]);
            upper = upper || isupper(password[i]);
            lower = lower || islower(password[i]);
            // skip characters while we are counting the same character
            // j should point to the first character which is not == password[i]
            for (j = i + 1; j < password.size() && password[j] == password[i]; ++j)
                ;
            if (j - i >= 3)
                repeats.push_back(j - i);
        }

        int missingConditions{!digit + !upper + !lower};
        int insertions{0};
        int deletions{0};
        if (password.size() < 6)
            insertions = 6 - password.size();
        else if (password.size() > 20)
            deletions = password.size() - 20;
        int operations = 0;

        // for every bad repeat, use insertions and missing conditions to break the repeat
        // insertion to break a repeat:
        //   AAAAAA -> AAAA_AA -> AA_AA_AA (reduces length of repeat by 2)
        // missing condition replacement to break a repeat:
        //   AAAAAA -> AAA_AA -> _AA_AA (reduces length of repeat by 3)
        for (size_t i = 0; i < repeats.size() && (insertions > 0 || missingConditions > 0); ++i)
        {
            while (repeats[i] >= 3 && insertions > 0)
            {
                --insertions;
                repeats[i] -= 2;
                ++operations;
                // if we are missing any conditions, this insertion can be used to satisfy that condition
                if (missingConditions > 0)
                    --missingConditions;
            }
            while (repeats[i] >= 3 && missingConditions > 0)
            {
                --missingConditions;
                repeats[i] -= 3;
                ++operations;
            }
        }

        // try to use deletions to break remaining long repeats
        // a deletion can only resolve a repeat by deleting length[i] - 2
        // we can use deletes to save replace operations later if we distribute them well
        // but we should use them to reduce repeats to (k*3)+2 if we can
        // because that will save on replace operations
        // replace twice : AAAAAA -> _AA_AA
        // delete replace: AAAAAA -> AA_AA
        // so we can go based on the modulus by 3
        // if (k*3+0) -> (k-1)*3+2 (just do one deletion)
        // if (k*3+1) -> (k-1)*3+2 (two deletions)
        // if (k*3+2) -> (k-1)*3+2->(k-2)*3+2->...->2 (3 deletions per iteration)
        for (int m = 0; m < 3; ++m)
        {
            if (deletions < m)
                break;
            for (int i = 0; i < repeats.size(); ++i)
            {
                if (repeats[i] < 3)
                    continue;
                while (repeats[i] >= 3 && deletions > m && repeats[i] % 3 == m)
                {
                    deletions -= m + 1;
                    repeats[i] -= m + 1;
                    operations += m + 1;
                }
            }
        }

        // any remaining long repeats can be satisfied with replacement
        // AAAAAAA -> A_AA_AA (length / 3 replacements)
        // AA -> AA (0 replacements needed)
        for (int i = 0; i < repeats.size(); ++i)
            operations += repeats[i] / 3;

        // any remaining insertions can satisfy any remaining conditions
        if (insertions > 0 && missingConditions > 0)
            missingConditions -= min(insertions, missingConditions);

        return operations + insertions + deletions + missingConditions;
    }
};