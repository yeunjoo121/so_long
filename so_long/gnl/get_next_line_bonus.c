#include "get_next_line.h"

int		isin_newline(char *str)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

int		ft_error(char **backup)
{
	while (*backup != 0)
	{
		free(*backup);
		*backup = 0;//프리하기 전 0 넣으면 메모리 주소가 사라지게 되므로 free할 수 없음.
	}
	return (-1);
}

int					get_one_line(char **backup, char **line, int cut)
{
	char			*temp;

	(*backup)[cut] = '\0';
	if (!(*line = ft_strdup(*backup)))
	{
		return (ft_error(backup));
	}
	if (!(temp = ft_strdup(*backup + cut + 1)))
	{
		return (ft_error(backup));
	}
	free(*backup);
	*backup = temp;
	return (1);
}

int					get_last(char **backup, char **line)
{
	int				cut;

	if (!(*backup))//file이 비어있을 때. backup[fd]가 아무것도 할당이 되지 않았으므로 여기에 들어간다.
	{
		*line = ft_strdup("");
		return (0);
	}
	else
	{
		if ((cut = isin_newline(*backup)) >= 0)
		//*backup == backup[fd]. *backup이 str의 제일 첫번째 주소값이므로 backup이 할당되어 있으면 아래로 들어감.
		//할당이 안되어있으면 위로 들어감.
		{
			return (get_one_line(backup, line, cut));
		}
		//newline이 없으면
		*line = ft_strdup(*backup);
		free(*backup);
		*backup = 0;
		return (0);
	}
}

int					get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				readsize;
	int				cut;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((readsize = read(fd, buf, BUFFER_SIZE)) > 0)//읽어들인 크기
	{
		buf[readsize] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		if ((cut = isin_newline(backup[fd])) >= 0)
			return (get_one_line(&backup[fd], line, cut));
	}
	if (readsize < 0)
	{
		return (ft_error(&backup[fd]));
	}
	return (get_last(&backup[fd], line));//읽어들인 게 0일 경우, backup에 남아있는 라인을 line에 저장.
}