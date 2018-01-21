#include <stdio.h>
#include <stdlib.h>

int savitzy_golay_filter(int *data,int index) {
    int approximated_value=0;
    // approximated_value=(1.0/35.0)*(-3.0*data[index-2] + 12.0*data[index-1]
                        // + 17.0*data[index] + 12.0*data[index+1] - 3.0*data[index+2]);
    approximated_value=(1.0/21.0)*(-2*data[index-3]+3*data[index-2]+
            6*data[index-1]+7*data[index]+6*data[index+1]+3*data[index+2]-2*data[index+3]);
    return approximated_value;
}

// window size is 3

void median_filter(int *array_data_smooth, int *array_data_smooth_median,int size_of_data) {
    int j=0,temp=0;
    for(j=0;j<size_of_data;j++) {
        if(j==0) {
            if(array_data_smooth[j]>array_data_smooth[j+1]) {
                array_data_smooth_median[j]=array_data_smooth[j];
            }
            else {
                array_data_smooth_median[j]=array_data_smooth[j+1];
            }
        }
        else {
            if(j==size_of_data-1) {
                if(array_data_smooth[j]>array_data_smooth[j-1]) {
                    array_data_smooth_median[j]=array_data_smooth[j];
                }
                else {
                    array_data_smooth_median[j]=array_data_smooth[j-1];
                }
            }
            else {
                temp=(array_data_smooth[j-1]>array_data_smooth[j]) ? array_data_smooth[j-1] : array_data_smooth[j];
                array_data_smooth_median[j]=(temp<array_data_smooth[j+1]) ? temp : array_data_smooth[j+1]; 
            }
        }
    }
    return;
}

// window size is 3

void moving_average_filter(int *array_data_smooth, int *array_data_smooth_average,int size_of_data) {
    int j=0;
    for(j=0;j<size_of_data;j++) {
        if(j==0) {
            array_data_smooth_average[j]=(array_data_smooth[j]+array_data_smooth[j+1])/2.0;
        }
        else {
            if(j==size_of_data-1) {
                array_data_smooth_average[j]=(array_data_smooth[j-1]+array_data_smooth[j])/2.0;
            }
            else {
                array_data_smooth_average[j]=(array_data_smooth[j-1]+array_data_smooth[j]+array_data_smooth[j+1])/3.0;
            }
        }
    }
    return;
}

int main(int argc, char *argv[]) {
    int size_of_data=0, temp=0, i=0, j=0, k=0;
    FILE *in;
    FILE *out;
    in=fopen(argv[1],"rw");
    
    // count number of entries in a file
    
    while(!feof(in)) {
        fscanf(in,"%d\n",&temp);
        size_of_data=size_of_data+1;
    }
    fclose(in);

    // dynamic allocation of memory to hold data; 

    int * array_data=(int *)malloc(sizeof(int)*(size_of_data+6));

    // read data from file and store it in array_data
    i=3;
    in=fopen(argv[1],"rw");
    while(!feof(in)) {
        fscanf(in,"%d\n",&array_data[i]);
        // printf("%d\n",array_data[i]);
        i=i+1;
    }
    fclose(in);

    /* 
    adding data before and after actual data for calculating approximate value 
    using at corners of signal while using savitzy_golay_filter
    */

    // array_data[0]=array_data[3];
    // array_data[0]=array_data[2];
    // array_data[1]=array_data[1];
    // array_data[size_of_data]=array_data[size_of_data-2];
    // array_data[size_of_data+1]=array_data[size_of_data-3];
    // array_data[size_of_data+2]=array_data[size_of_data-4];

    array_data[0]=array_data[3];
    array_data[1]=array_data[2];
    array_data[2]=array_data[1];
    array_data[size_of_data]=array_data[size_of_data-2];
    array_data[size_of_data+1]=array_data[size_of_data-3];
    array_data[size_of_data+2]=array_data[size_of_data-4];

    // data smoothening

    int * array_data_smooth=(int *)malloc(sizeof(int)*size_of_data);

    for(j=0;j<size_of_data;j++) {
        // j+3 because actual data starts after two positions
        array_data_smooth[j]=savitzy_golay_filter(array_data,j+3);
    }

    // apply median filter
    
    int * array_data_smooth_median=(int *)malloc(sizeof(int)*size_of_data);

    median_filter(array_data_smooth,array_data_smooth_median,size_of_data);

    // apply average filter

    int * array_data_smooth_average=(int *)malloc(sizeof(int)*size_of_data);
    
    moving_average_filter(array_data_smooth,array_data_smooth_average,size_of_data);

    // smoothening moving average data by savitzy golay filter

    for(j=0;j<size_of_data;j++) {
        array_data[j+3]=array_data_smooth[j];
    }

    array_data[0]=array_data[3];
    array_data[1]=array_data[2];
    array_data[2]=array_data[1];
    array_data[size_of_data]=array_data[size_of_data-2];
    array_data[size_of_data+1]=array_data[size_of_data-3];
    array_data[size_of_data+2]=array_data[size_of_data-4];

    int * array_data_smooth_average_smooth=(int *)malloc(sizeof(int)*size_of_data);

    for(j=0;j<size_of_data;j++) {
        // j+3 because actual data starts after two positions
        array_data_smooth_average_smooth[j]=savitzy_golay_filter(array_data,j+3);
    }

    // writing smoothed data to a file

    out=fopen("data_smooth.csv","w");
    for(j=0;j<size_of_data;j++) {
        fprintf(out,"%d\n",array_data_smooth[j]);
    }
    fclose(out);

    /*
     writing data to a file after applying median filter on data 
    smoothed by savitzy golay filter
    */
    out=fopen("data_smooth_median.csv","w");
    for(j=0;j<size_of_data;j++) {
        fprintf(out,"%d\n",array_data_smooth_median[j]);
    }
    fclose(out);

    /* 
    writing data to a file after applying mean filter on data 
    smoothed by savitzy golay filter
    */
    out=fopen("data_smooth_average.csv","w");
    for(j=0;j<size_of_data;j++) {
        fprintf(out,"%d\n",array_data_smooth_average[j]);
    }
    fclose(out);

    /*
     writing data after applying again savitzy golay filter on data 
     smoothed by savitzy golay filter and mean filter
    */

    out=fopen("data_smooth_average_smooth.csv","w");
    for(j=0;j<size_of_data;j++) {
        fprintf(out,"%d\n",array_data_smooth_average_smooth[j]);
    }
    fclose(out);

    /*
     detection of peaks and calculation of heart beat using data smoothed by 
    savitzy golay filter, mean filter, savitzy golay filter
    */

    int flag=0, count=0;
    int *array_peak_positions=(int *)calloc(sizeof(int),(size_of_data/2));

    for(j=0;j<size_of_data;j++) {
        if((array_data_smooth_average_smooth[j]>520 && array_data_smooth_average_smooth[j-1]>520) && (array_data_smooth_average_smooth[j] >= array_data_smooth_average_smooth[j-1])) {
            flag=1;
        }
        else {
            if(flag==1) {
                if(k>0) {
                    int diff=j-1-array_peak_positions[k-1];

                    // for neglecting peaks near by and taking maximum of them

                    if(diff > 30) {
                        array_peak_positions[k]=j-1;
                        // printf("%d = %d\n",j-1, array_data_smooth_average_smooth[j-1]);
                        k=k+1;
                        count=count+1;
                        flag=0;
                    }
                    else {
                        if(array_data_smooth_average_smooth[array_peak_positions[k-1]]<array_data_smooth_average_smooth[j-1]) {
                            array_peak_positions[k-1]=j-1;
                            flag=0;
                        }
                        else {
                            flag=0;
                        }
                    }
                }
                else {
                    array_peak_positions[k]=j-1;
                    // printf("%d = %d\n",j-1, array_data_smooth_average_smooth[j-1]);
                    k=k+1;
                    count=count+1;
                    flag=0;
                }
            }
            else {
                flag=0;
            }
        }
    }

    out=fopen("peak_points.csv","w");
    for(j=0;j<count;j++) {
        fprintf(out,"%d %d\n",array_peak_positions[j],array_data_smooth_average_smooth[array_peak_positions[j]]);
    }
    fclose(out);
    
    printf("heart beat = %d\n",count);

    // float heart_rate=0, heart_rate_average=0;

    // for(j=0;j<count-1;j++) {
    //     heart_rate=(6000.0)/(array_peak_positions[j+1]-array_peak_positions[j]);
    //     // printf("heart_rate = %0.2f\n",heart_rate);
    //     heart_rate_average=heart_rate_average+heart_rate;
    // }

    // printf("heart_rate average = %0.2f\n", (heart_rate_average/(j)));

    return 0;
}