# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/12/04 12:59:28 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ***************************** CONFIGURATION ******************************** #

NAME			:=	server
CLIENT			:=	client

# Header files directories:
I				:=	inc/ libft/inc/

#
L				:=	libft/
l				:=	ft

# Build direcoties:
B				:=	build/
D				:=	$B_dep/
O				:=	$B_obj/

# Source files directory:
S				:=	src/

# Makefiles in build/ directory with source file listings to be included
# (files that are dependent on others need to be below their dependency):
SOURCELISTS		:=	client.mk \
					server.mk \

# Flags:
CC				:=	cc
CFLAGS			:=	-Wall -Wextra -Werror $(addprefix -I,$I)
DEBUGFLAGS		:=	-g


# ***************************** BUILD PROCESS ******************************** #

.DEFAULT_GOAL	:=	all

include				$(addprefix $B,$(SOURCELISTS))

SRC				:=	$(foreach name,$(basename $(SOURCELISTS)),$(SRC_$(name)))

DEP				:=	$(SRC:%.c=$D%.d)
OBJ_CLIENT		:=	$(SRC_client:%.c=$O%.o)
OBJ_SERVER		:=	$(SRC_server:%.c=$O%.o)
OBJ				:=	$(OBJ_SERVER) $(OBJ_CLIENT)
SUBDIRS_D		:=	$(sort $(dir $(DEP)))
SUBDIRS_O		:=	$(sort $(dir $(OBJ)))

PREVIOUS_GOAL	=	$(shell cat $B.previous_goal 2>/dev/null)

export 				MAKECMDGOALS

.PHONY			:	all bonus lib cleandep cleanobj clean fclean re debug debuglib \
					norm print-% dir

ifneq ($(PREVIOUS_GOAL),$(filter $(PREVIOUS_GOAL),$(MAKECMDGOALS)))
all				:	fclean lib $(NAME)
    ifeq (,$(filter debug,$(MAKECMDGOALS)))
	@				echo "Last target was debug, so recompiled everything."
    endif
else
all				:	lib $(NAME) $(CLIENT)
endif

bonus			:	all

lib				:
	@				make -C $L --no-print-directory

$(NAME)			:	$L $(OBJ_SERVER) | lib
					$(CC) $(CFLAGS) $(OBJ_SERVER) $(addprefix -L,$L) \
					$(addprefix -l,$l) -o $@

$(CLIENT)		:	$L $(OBJ_CLIENT) | lib
					$(CC) $(CFLAGS) $(OBJ_CLIENT) $(addprefix -L,$L) \
					$(addprefix -l,$l) -o $(CLIENT)

$(CLIENT)-%		:	$L $(OBJ_CLIENT) | lib
					$(CC) $(CFLAGS) $(OBJ_CLIENT) $(addprefix -L,$L) \
					$(addprefix -l,$l) -o $@

$(OBJ):	$O%.o	:	$S%.c | $(SUBDIRS_O)
					$(CC) $(CFLAGS) -c $< -o $@

$(DEP):	$D%.d	:	$S%.c | $(SUBDIRS_D)
	@				$(CC) $(CFLAGS) -M -MP -MF $@ -MT "$O$*.o $@" $<

$(SUBDIRS_O) $(SUBDIRS_D):
	@				mkdir -p $@

cleandep		:
ifeq (,$(filter clean fclean re debug,$(MAKECMDGOALS)))
	@			make -C $L cleandep --no-print-directory
endif
ifneq (,$(wildcard $(DEP)))
				rm -f $(DEP)
endif
ifneq (,$(wildcard $D))
				-find $D -type d -empty -delete
endif

cleanobj		:
ifeq (,$(filter clean fclean re debug,$(MAKECMDGOALS)))
	@			make -C $L cleanobj --no-print-directory
endif
ifneq (,$(wildcard $(OBJ)))
				rm -f $(OBJ)
endif
ifneq (,$(wildcard $O))
				-find $O -type d -empty -delete
endif

clean			:	cleandep cleanobj
ifneq ($(PREVIOUS_GOAL),debug)
    ifeq (,$(filter fclean re debug,$(MAKECMDGOALS)))
	@				make -C $L clean --no-print-directory
    endif
endif

fclean			:	clean
ifeq (,$(filter debug,$(MAKECMDGOALS)))
	@				make -C $L fclean --no-print-directory
endif
ifneq (,$(wildcard $B.previous_goal))
					rm -f $B.previous_goal
endif
ifneq (,$(wildcard $(NAME) $(CLIENT)))
					rm -f $(NAME) $(CLIENT)*
endif

re				:	fclean all

debug			:	CFLAGS += $(DEBUGFLAGS)
ifneq ($(PREVIOUS_GOAL),debug)
debug			:	debuglib re
	@				echo "$@" > $B.previous_goal
else
export				CFLAGS
debug			:	all
endif

debuglib		:
	@				make -C $L debug --no-print-directory

dir				:
					mkdir $B $I $L $S

norm			:
	@				-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
					$(addprefix $S,$(SRC)) $(foreach dir,$I,$(dir)*.h)
	@				make -C $L norm --no-print-directory

ifeq (,$(filter cleandep cleanobj clean fclean re norm,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $O))
        -include	$(DEP)
    endif
endif


# *************************** MAKEFILE DEBUGGING ***************************** #

# Makefile debugging
print-%			:
	@				echo $* = $($*)
