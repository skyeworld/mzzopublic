/*************************************************************************
    > File Name: 16.c
    > Author: chaofei
    > Mail: chaofeibest@163.com 
    > Created Time: 2019-03-09 13:59:22
 ************************************************************************/

#include <stdio.h>

long int f(int year, int month) {
  /*f(年, 月) = 年-1, 如月<3; 否则,f(年, 月) = 年*/ 
  if (month  < 3) {
    return year - 1;
  } else {
    return year;
  }
}

long int g(int month) {
  /*g(月) = 月+13,如月<3; 否则,g(月) = 月+1*/
  if (month < 3) {
    return month + 13;
  } else {
    return month + 1;
  }
}

long int n(int year, int month, int day) {
  /*N = 1461*f(年, 月)/4 + 153*g(月)/5 + 日*/
  /*4年一个闰年4*356+1=1461; */
  return 1461L * f(year, month) / 4 + 153L * g(month) / 5 + day;
}

int w(int year, int month, int day) {
  /*w = (N-621049) % 7(0 <= w < 7)*/
  return (int)((n(year, month, day) % 7 - 621049L % 7 + 7) % 7);
}

int is_leap_year(int year) {
  /*判断是否是闰年*/
  if (year % 4 == 0 && year % 100 != 0 && year % 400 == 0) {
    return 1;
  }
  return 0;
}

int date[12][6][7];
/*闰年的2月为29天*/
int day_tbl[][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, 
                     {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/*
 * 原因：若一年按365天5h48'46''（此时86400年也是闰年）计算，一年日数必须是整数，不便将零时数计入，
 * 所以取365天为一年，则余5时48分46秒 ，积至4年约满一 日，所以4年一“闰日”，谓之“闰年”，
 * 无“闰日”之年为平年，即平年365天，闰年366天。但到4年之时，仅有23时15分4秒闰一日，欠缺44分56秒；
 * 积至100年（25闰）时就欠缺18时43分20秒，约合3 / 4日，所以满100年不闰；此时又余5时16分40秒，
 * 积至400年余21时6分40秒又闰；又欠缺2时53分20秒，积至3200年计欠缺23时6分40秒，所以满3200年不闰；
 * 此时又余53分20秒，积至86400年刚好24 时又一闰，这是不余不欠，需重计算，所以按阳历计算就有上面的闰年规则。
 *
 * 按一回归年365天5h48'45.5''计算：3200年多出16000小时153600分145600秒 =18600小时26分40秒，
 * 现行公历中每400年有97个闰年，3200年共97*8=776个闰年=776*24小时 [1]  =18624小时 >18600小时，所以只能算到775个闰年，
 * 3200不是闰年，于是775*24=18600，多出了26分40秒怎么办需要多少个周期弥补？
 * 答案是54个周期，为172800年，因为172800/3200=54个周期 54*26分40秒=1404分2160秒=24小时。
 */

int main(void) {
  int sw, leap, i, j, k, wd, day;
  int year; /*年*/
  char title[] = "SUM MON TUR WED THU FRI SAT";
  printf("Please input the year whose calendar you want to know:"); /*输出年*/
  scanf("%d", &year); /*输入年份值*/
  /*计算年的sw*/
  sw = w(year, 1, 1);
  //leap = is_leap_year(year);
  leap=year%4==0&&year%100||year%400==0;/*判闰年*/

  /*日期表置0*/
  for (i = 0; i < 12; ++i) {
    for (j = 0; j < 6; ++j) {
      for (k = 0; k < 7; ++k) {
        date[i][j][k] = 0;
      }
    } 
  }

  for (i = 0; i < 12; ++i) {
    for (wd = 0, day = 1; day <= day_tbl[leap][i]; ++day) {
      date[i][wd][sw] = day;
      /*每星期七天,以0至6计数*/
      sw = ++sw % 7;
      if (sw == 0) {
        /*日期表每7天一行,星期天开始新的一行*/
        ++wd;
      }
    }
  }

  printf("\n|==================The Calendar of Year %d =====================|\n|", year);
  for (i = 0; i < 6; ++i) {
    /*西安测算第i+1和第i+7月的最大星期数*/;
    /*日期表的第六行有日期,则wd!=0*/;
    for (wd = 0, k = 0; k < 7; ++k) {
      wd += date[i][5][k] + date[i+6][5][k];
      wd = wd? 6: 5;
      printf("%2d  %s  %2d  %s |\n|",i+1,title,i+7,title);
      for (j = 0; j < wd; ++j) {
        printf("    "); /*输出四个空白符*/
        for (k = 0; k < 7; ++k) {
          if (date[i][j][k]) {
            printf("%4d", date[i][j][k]);
          } else {
   //         printf("   "); /*输出3个空白符*/
            printf("   ");/*输出四个空白符*/
          }
        }
  //      printf("     "); /*输出5个空白符*/
          printf("     ");
        for (k = 0; k< 7; ++k) {
          if (date[i+6][j][k]) {
            printf("%4d", date[i+6][j][k]);
          } else {
            printf("    ");
            printf("    ");
          }
        }
        printf(" |\n|");
//        printf(" |\n|");
      }
    }
  }
  puts("=================================================================|");
  return 0;
}
