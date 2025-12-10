#pragma once
#include <iostream>

#include "../../core/clsAdmin.h"
#include "../../core/clsBankClient.h"

clsAdmin CurrentAdmin = clsAdmin::Find("","");
clsBankClient CurrentClient = clsBankClient::Find("","");
