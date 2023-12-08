# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    server.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 13:33:38 by ldulling          #+#    #+#              #
#    Updated: 2023/12/08 15:50:46 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ****************************** PREPARATION ********************************* #

# Gets this file's name (without suffix) for automatic variable creation later.
FILENAME	:=	$(basename $(notdir $(lastword $(MAKEFILE_LIST))))

# Resets TMP to get rid of any old values from other .mk files.
TMP			:=


# ***************************** CONFIGURATION ******************************** #

# Dependencies - has to be the basename of the corresponding .mk file:
DEPS	:=

# Directory of source files in src/ directory:
DIR		:=	./

# Source files:
#  Server:
SUBDIR	:=	server/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			01_handshake_server.c \
			02_get_len.c \
			03_buffer_msg.c \
			04_display_msg.c \
			server.c \
			server_utils.c \
)


# *************************** VARIABLE CREATION ****************************** #

# Creates a final SRC variable and assigns all the source files specified above.
$(eval SRC_$(FILENAME)		:=	$(TMP))

# Creates an OBJ variable for the dependency rule below.
$(eval OBJ_$(FILENAME)		:=	$(SRC_$(FILENAME):%.c=$O%.o))

# Makes this file's object files dependent on any DEPS specified above.
$(OBJ_$(FILENAME)):	$O%.o	:	$(foreach dep,$(DEPS),$(OBJ_$(dep)))


# *************************** MAKEFILE DEBUGGING ***************************** #

# Prints the values of the variable given after the minus.
print-%	:
	@		echo $* = $($*)
