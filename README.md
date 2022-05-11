```ignoreleak
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}
```

```shell
valgrind --suppressions=ignoreleak --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
```

<< "" ls

export :
	trier par ordre ascii
	sans les guillemets

error 126 : essaye d'executer un non executable
