#include "cube3d.h"

// void check_player(char **myarr,int i,int j,t_map *map)
// {
// 	// t_map *map;
// 	if (ft_strchr("NEWS", myarr[i][j]))
// 				{
// 					if (i == 0 || j == 0 || i == map->rows - 1
// 						|| j == ft_strlen(myarr[i]) - 1)
// 						printerr(1,
// 							"Error : Invalid map not surrounded by valid characters");
// 					if (!((i > 0 && (myarr[i - 1][j] == '0' || myarr[i
// 									- 1][j] == '1')) && (i < map->rows - 1
// 								&& (myarr[i + 1][j] == '0' || myarr[i
// 									+ 1][j] == '1')) && (j > 0 && (myarr[i][j
// 									- 1] == '0' || myarr[i][j - 1] == '1'))
// 							&& (j < ft_strlen(myarr[i]) - 1 && (myarr[i][j
// 									+ 1] == '0' || myarr[i][j + 1] == '1'))))
// 						printerr(1,
// 							"Error : Invalid map not surrounded by valid characters");
// 				}
// }
// void check_zero(char **myarr,int i,int j,t_map *map)
// {
// 	// t_map *map;
//     // printf("%d %")
// 	if (myarr[i][j] == '0')
// 				{
// 					if (i == 0 || j == 0 || i == map->rows - 1
// 						|| j == ft_strlen(myarr[i]) - 1)
// 						printerr(1,
// 							"Error : Invalid map not surrounded by valid characters");
// 					if (!((i > 0 && (myarr[i - 1][j] == '0' || myarr[i
// 									- 1][j] == '1' || ft_strchr("NEWS", myarr[i
// 										- 1][j]))) && (i < map->rows - 1
// 								&& (myarr[i + 1][j] == '0' || myarr[i
// 									+ 1][j] == '1' || ft_strchr("NEWS", myarr[i
// 										+ 1][j]))) && (j > 0 && (myarr[i][j
// 									- 1] == '0' || myarr[i][j - 1] == '1'
// 									|| ft_strchr("NEWS", myarr[i][j - 1])))
// 							&& (j < ft_strlen(myarr[i]) - 1 && (myarr[i][j
// 									+ 1] == '0' || myarr[i][j + 1] == '1'
// 									|| ft_strchr("NEWS", myarr[i][j + 1])))))
// 					{
// 						printerr(1,
// 							"Error : Invalid map not surrounded by valid characters");
// 					}
// 				}
// }
// void check_space(char **myarr,int i,int j,t_map *map)
// {
// 	// t_map *map;
// 	if (myarr[i][j] == ' ')
// 				{
// 					if (i > 0 && j > 0 && i < map->rows - 1
// 						&& j < ft_strlen(myarr[i]) - 1)
// 					{
// 						if (!((myarr[i - 1][j] == ' ' || myarr[i - 1][j] == '1')
// 								&& (myarr[i + 1][j] == ' ' || myarr[i
// 									+ 1][j] == '1') && (myarr[i][j - 1] == ' '
// 									|| myarr[i][j - 1] == '1') && (myarr[i][j
// 									+ 1] == ' ' || myarr[i][j + 1] == '1')))
// 						{
// 							printerr(1,
// 								"Error: Invalid map not surrounded by valid characters");
// 						}
// 					}
// 				}
// }
void check_zero(char **myarr,t_map *map,int i,int j)
{
	if (myarr[i][j] == '0' ) 
    {
	   if (i == 0 || j == 0 || i == map->rows - 1  || j==ft_strlen(myarr[i])-1)
	       printerr(1,"Error : Invalid map not surrounded by valid characters");
	   if (!( (i > 0 && (myarr[i-1][j] == '0' || myarr[i-1][j] == '1' || ft_strchr("NEWS", myarr[i-1][j])) )&&
	       (i < map->rows-1 && (myarr[i+1][j] == '0' || myarr[i+1][j] == '1' || ft_strchr("NEWS", myarr[i+1][j]))) &&
	        (j > 0 && (myarr[i][j-1] == '0' || myarr[i][j-1] == '1' || ft_strchr("NEWS", myarr[i][j-1]))) &&
	      ( j < ft_strlen(myarr[i]) - 1 &&  (myarr[i][j+1] == '0' || myarr[i][j+1] == '1' || ft_strchr("NEWS", myarr[i][j+1])) )))
	   {
	       printerr(1,"Error : Invalid map not surrounded by valid characters");
	   }
    }
}
void check_player(char **myarr,t_map *map,int i,int j)
{
if(ft_strchr("NEWS", myarr[i][j]))
    {
	   if (i == 0 || j == 0 || i == map->rows - 1 || j==ft_strlen(myarr[i])-1)
	       printerr(1,"Error : Invalid map not surrounded by valid characters");
	   if (!(( i>0 && (myarr[i-1][j] == '0' || myarr[i-1][j] == '1' ) )&&
	       (i < map->rows-1 && (myarr[i+1][j] == '0' || myarr[i+1][j] == '1' )) &&
	       (j > 0 && (myarr[i][j-1] == '0' || myarr[i][j-1] == '1' )) &&
	       ( j < ft_strlen(myarr[i]) - 1 && (myarr[i][j+1] == '0' || myarr[i][j+1] == '1' ) )))
	       printerr(1,"Error : Invalid map not surrounded by valid characters");
    }
}
void check_space(char **myarr,t_map *map,int i,int j)
{
if(myarr[i][j]==' ')
    {
	    if (i > 0 && j > 0 && i < map->rows - 1 && j < ft_strlen(myarr[i]) - 1) {
	   if (!( (myarr[i-1][j] == ' ' || myarr[i-1][j] == '1') &&
	          (myarr[i+1][j] == ' ' || myarr[i+1][j] == '1') &&
	          (myarr[i][j-1] == ' ' || myarr[i][j-1] == '1') &&
	          (myarr[i][j+1] == ' ' || myarr[i][j+1] == '1'))) {
	       printerr(1, "Error: Invalid map not surrounded by valid characters");
	   }
        }
    }
}
// int	isvalid_map(t_map *map, char **myarr)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < map->rows && myarr[i])
// 	{
// 		j = 0;
		
// 			while (j < ft_strlen(myarr[i]))
// 			{
// 				check_zero(myarr,map,i,j);
// 				check_player(myarr,map,i,j);
// 				check_space(myarr,map,i,j);
// 				j++;
// 			}
// 		i++;
// 	}
// 	return (1);
// }

int isvalid_map(t_map *map, char **myarr)
{
    int i = 0;
    int j = 0;

    while (i< map->rows && myarr[i])
    {
        j = 0;
        while (j < ft_strlen(myarr[i]))
        {   
            if (myarr[i][j] == '0' )
            {
                    if (i == 0 || j == 0 || i == map->rows - 1  || j==ft_strlen(myarr[i])-1)
                        printerr(1,"Error : Invalid map not surrounded by valid characters");
                    if (!( (i > 0 && (myarr[i-1][j] == '0' || myarr[i-1][j] == '1' || ft_strchr("NEWS", myarr[i-1][j])) )&&
                        (i < map->rows-1 && (myarr[i+1][j] == '0' || myarr[i+1][j] == '1' || ft_strchr("NEWS", myarr[i+1][j]))) &&
                         (j > 0 && (myarr[i][j-1] == '0' || myarr[i][j-1] == '1' || ft_strchr("NEWS", myarr[i][j-1]))) &&
                       ( j < ft_strlen(myarr[i]) - 1 &&  (myarr[i][j+1] == '0' || myarr[i][j+1] == '1' || ft_strchr("NEWS", myarr[i][j+1])) )))
                    {
                        printerr(1,"Error : Invalid map not surrounded by valid characters");
                    }
                }
                if(ft_strchr("NEWS", myarr[i][j]))
                {
                    if (i == 0 || j == 0 || i == map->rows - 1 || j==ft_strlen(myarr[i])-1)
                        printerr(1,"Error : Invalid map not surrounded by valid characters");
                    if (!(( i>0 && (myarr[i-1][j] == '0' || myarr[i-1][j] == '1' ) )&&
                        (i < map->rows-1 && (myarr[i+1][j] == '0' || myarr[i+1][j] == '1' )) &&
                        (j > 0 && (myarr[i][j-1] == '0' || myarr[i][j-1] == '1' )) &&
                        ( j < ft_strlen(myarr[i]) - 1 && (myarr[i][j+1] == '0' || myarr[i][j+1] == '1' ) )))
                        printerr(1,"Error : Invalid map not surrounded by valid characters");
                }
                if(myarr[i][j]==' ')
                {
                     if (i > 0 && j > 0 && i < map->rows - 1 && j < ft_strlen(myarr[i]) - 1) {
                    if (!( (myarr[i-1][j] == ' ' || myarr[i-1][j] == '1') &&
                           (myarr[i+1][j] == ' ' || myarr[i+1][j] == '1') &&
                           (myarr[i][j-1] == ' ' || myarr[i][j-1] == '1') &&
                           (myarr[i][j+1] == ' ' || myarr[i][j+1] == '1'))) {
                        printerr(1, "Error: Invalid map not surrounded by valid characters");
                    }
                     }
                }
            j++;
            }
        i++;
    }
    return 1;
}
