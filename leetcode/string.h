//
// Created by ZhouP on 3/3/2019.
//

#ifndef CPP_STRING_H
#define CPP_STRING_H


int testString(    std::string s)
{
    int len = s.length();
    if (len<=1)
    {
        return len;
    }
    unsigned int current[255];
    memset(current, 0, 255*sizeof(unsigned int));
//    unsigned int* lens = new unsigned int[len];
    int valid_index  = 0;
    std::vector<int> lens;
    for (int i = 0; i < len; ++i) {
        lens.push_back(0);
        const char c = s[i];
        int index = (int)(c-' ');
        if (current[index]>valid_index)
        {
            for(int j=valid_index; j<current[index];++j)
            {
                lens[j] = i-j;
            }

            valid_index = current[index];
        }

        current[index]=i+1;
        lens[i] = len - i;
    }

    return *std::max_element(lens.begin(), lens.end());
}
//
//printf("%d\n", testString("   "));
//printf("%d\n", testString("aabaab!bb"));

#endif //CPP_STRING_H
