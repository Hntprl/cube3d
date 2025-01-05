#include "cube3d.h"

void printerr(int status,char *str)
{
	printf("%s\n",str);
	exit(status);
}

void checkpath(char *av)
{
	if(ft_strcmp(av+ft_strlen(av)-4,".cub"))
		printerr(1,"Error: The file must end with .cub");
}

int is_validtexture(char **str)
{
	//  if (ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 || ft_strncmp(line, "NO", 2) == 0)
	if((!ft_strcmp(str[0],"NO") || !ft_strcmp(str[0],"SO") || !ft_strcmp(str[0],"WE") || !ft_strcmp(str[0],"EA")) && (ft_strlen(str[1]) > 4))
			return 0;
	else 
		return 1;
		
}
int	is_space(char str)
{
	if (str == ' ' || str == '\n' || str == '\t' || str == '\v' || str == '\f'
		|| str == '\r')
		return (1);
	return (0);
}
int count_words(const char *str) 
{
    int count = 0;
    int in_word = 0;

    while (*str) 
	{
        if (!is_space(*str)) 
		{
            if (!in_word) 
			{
                in_word = 1; 
                count++;
            }
        } else {
            in_word = 0;
        }
        str++;
    }
    return count;
}
	// if(map->map)
	// 	printerr(1,"the map shouldn't be initialized before textures");
	//should firslty have just 2 strings
void fill_textures(t_map *map,char *str)
{
	char **string;
	int i=0;
	map->no_img=calloc(1,sizeof(char *));
	map->su_img=calloc(1,sizeof(char *));
	map->es_img=calloc(1,sizeof(char *));
	map->we_img=calloc(1,sizeof(char *));
	string=ft_split(str,' ');
	if(count_words(str)>2)
		printerr(1,"Error : the args of textures must be 2");
	int j=0;
	while (string[j])
	{
		string[j]=ft_strtrim(string[j]," \t\n");
		j++;
	}
	// printf("line %s\n",string[1]+ft_strlen(string[1])-4);
	if ((ft_strcmp(string[1]+ft_strlen(string[1])-4,".xpm")))//maybe work with strcmp
				printerr(1,"the texture should end with .xpm");
	if(!(is_validtexture(string)))
	{
			if(str[0]=='N')
				map->no_img=string[1];
			else if(str[0]=='S')
				map->su_img=string[1];
			else if(str[0]=='W')
				map->we_img=string[1];
			else if(str[0]=='E')
				map->es_img=string[1];
	}
	else
		printerr(1,"the textures should have one of the directions < NO, SO, WE, EA > ");
}
		// while (last_non_space==str && is_space(*str))//when the format like that <F 220,200, ,4 >
        // 	str++;
	// printf("valid format *%s*",str);

int is_valid_format(char *str) 
{
    while (is_space(*str))
        str++;
    if (!str || *str == '\0')
        return 0; 
    int last_was_comma = 0;
    if (*str == ',')
        return 0; 
    char *last_non_space = NULL;
    while (*str) 
	{
        if (!is_space(*str))
            last_non_space = str;
        if (*str == ',') 
		{
            if (last_was_comma)
                return 0; 
            last_was_comma = 1;
        } 
		else
            last_was_comma = 0;
        str++;
    }

    if (last_non_space && *last_non_space == ',')
        return 0;
    return 1; 
}
int isnot_alpha(char *str)
{
	while(*str)
	{
	if (!ft_isdigit(*str) && *str != ',' && !is_space(*str)) 
            return 0;
		str++;
	}
	return 1;
}
void is_validcolor(char *str)
{
	if(!(is_valid_format(str)) || !(isnot_alpha(str)))
		printerr(1,"Error : the correct format (R, G, B)");
	char **split=ft_split(str,',');
	if (split[3])
		printerr(1, "Error: Colors have 3 elements (R, G, B)");
	free(split);
}
int *min_fill(t_map *map, char *str, int i, int start)
{
    int valid_range = 0;
    char *substr;
    static int ce_index = 0; 
    static int fl_index = 0; 

    if (ce_index == 0 && fl_index == 0) 
	{
        map->ce_color = calloc(3, sizeof(int));
        map->fl_color = calloc(3, sizeof(int));
    }
    substr = ft_substr(str, start, i);
    valid_range = atoi(substr);
    free(substr);
    if (valid_range < 0 || valid_range > 255) 
	{
        printerr(1, "Error: The color range should be between 0 & 255");
        return NULL;
    }
    if (str[0] == 'C') 
	{
        if (ce_index < 3)
            map->ce_color[ce_index++] = valid_range;
    }
	 else if (str[0] == 'F') 
	{
        if (fl_index < 3)
            map->fl_color[fl_index++] = valid_range;
    }
    return NULL;
}

void	spliit(char *str,t_map *map)
{
	int i=1;
	int start=0;

	is_validcolor(str+1);
	while(str[i])
	{
		while(str[i] && (str[i] == ' ' || str[i] == '\t' ))
    		i++;
		start=i;
		while(str[i] && ft_isdigit(str[i]))
			i++;
		if( start<i )
			min_fill(map,str,i,start);
		else if(str[i] == ',')
			i++;
		i++;
	}
}

void fill_colors(t_map *map,char *str)
{
	if((str[0]=='C' || str[0]=='F') && str[1]==' ' || str[1]=='	')
		spliit(str,map);
	else
		printerr(1,"error the format of color invalid");
}