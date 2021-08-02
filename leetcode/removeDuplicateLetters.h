//
// Created by ZhouP on 4/17/2019.
//

//Given the string s, the greedy choice (i.e., the leftmost letter in the answer) is the smallest s[i], s.t.
//the suffix s[i .. ] contains all the unique letters. (Note that, when there are more than one smallest s[i]'s, we choose the leftmost one. Why? Simply consider the example: "abcacb".)
//
//After determining the greedy choice s[i], we get a new string s' from s by
//
//removing all letters to the left of s[i],
//        removing all s[i]'s from s.

#ifndef CPPSANDBOX_REMOVEDUPLICATELETTERS_H
#define CPPSANDBOX_REMOVEDUPLICATELETTERS_H


string removeDuplicateLetters(string s)
{
    vector<int> alphabetCount( 26, 0 );
    string buffer;
    int index, pos = 0;

    for( index = 0; index < s.length( ); index++ )
    {
        alphabetCount[ s[ index ] - 'a' ]++;
    }

    for( index = 0; index < s.length( ); index++ )
    {
        if( s[ index ] < s[ pos ] )
        {
            pos = index;
        }

        alphabetCount[ s[ index ] - 'a' ]--;

        if( alphabetCount[ s[ index ] - 'a' ] == 0 )
        {
            break;
        }
    }

    if( s.empty( ) )
    {
        return "";
    }
    else
    {
        buffer = s.substr( pos + 1 );
        buffer.erase( remove( buffer.begin( ), buffer.end( ), s[ pos ] ), buffer.end( ) );

        return s[ pos ] + removeDuplicateLetters( buffer );
    }
}

#endif //CPPSANDBOX_REMOVEDUPLICATELETTERS_H
