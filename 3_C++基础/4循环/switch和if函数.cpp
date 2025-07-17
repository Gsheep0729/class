#include <iostream>

int main()
{
    double a = 0.000;
    double b = 0.000;
    char c = '0';
    std::cout << "ÇëÊäÈë£ºÊý×Ö-ÔËËã·û-Êý×Ö";
    std::cin >> a >> c >> b ;
    switch ( c )
    {
      case  '+':
        std::cout << a << c << b << "=" << a+b;
        break;
      case  '-':
        std::cout << a << c << b << "=" << a-b;
        break;
      case  '*':
        std::cout << a << c << b << "=" << a*b;
        break;
      case  '/':
        if ( b == 0)   //»òÕß if( b != 1 )
        {   
          std::cout << "²»ÄÜ³ýÒÔÁã" ;
        }
        else
        {
        std::cout << a << c << b << "=" << a/b;
        }
        break;



        
    }
    return 0;
}


//¢Ù1111111111111
//{

  // int a = 59  ;
   //if( a >= 60)
   //{
     // std::cout << "¾íÄãÂè"   ; 
    //}
    //else
    //{
      //std::cout << "Ð»Ð»ÐÖµÜ"  ;
    //}
   //return 0;
//}
   //¢Ú222222222222
  // {
  //int score = 81;
  //int level = score / 10;
//switch (level)
//{
    //case 10:
    //case 9:
    //std::cout << "A" << std::endl;
    //break;
    //case 8:
    //std::cout << "B" << std::endl;    

    //case 7:
    //std::cout << "C" << std::endl;
    //case 6:
    //std::cout << "D" << std::endl;
    //break;
    //default:
    //std::cout << "E" << std::endl;
    //break;
//}
    //return 0;
//}
    