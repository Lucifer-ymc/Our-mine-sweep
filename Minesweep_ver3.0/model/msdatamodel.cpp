#include "msdatamodel.h"

MSDataModel::MSDataModel():b(std::make_shared<Block>(8,8,10))
{

}

std::shared_ptr<Block> MSDataModel :: get_block() throw(){
    return b;
}

bool MSDataModel :: restart(int row, int col, int boom_num){
    Fire_OnPropertyChanged("restart");
    b->re_construct(row, col, boom_num);
    return 1;
}
//7.20 wzq:fix the problem of overflow at bound of map
bool MSDataModel::leftclick(int x_pos, int y_pos){
    if(b->p[x_pos][y_pos].get_show()==0){//leftclick on block unvisited
        if(b->p[x_pos][y_pos].get_boom()==1){//leftclick on boom block
            b->set_play(0);
            b->set_lose(1);
            Fire_OnPropertyChanged("lose");
            b->set_lock(1);//7.18 using is_lock
            return 1;
        }else{
            Fire_OnPropertyChanged("block");
            b->bset_show(x_pos, y_pos);
            b->reset_visit(x_pos, y_pos);
            return 1;
        }
    }else if(b->p[x_pos][y_pos].get_show()==1){//leftclick on block visited
        int cnt=0;//num of flags around the certain block
        for(int i=x_pos-1;i<=x_pos+1;i++){
            for(int j=y_pos-1;j<=y_pos+1;j++){
                if(i==-1||j==-1||i==b->get_row()||j==b->get_col()){//overflow
                    //continue;
                }else if(b->p[i][j].get_flag()==1){
                    cnt++;
                }
            }
        }

        if(cnt==b->p[x_pos][y_pos].get_sur()){//all booms around it has been flaged
            for(int i=x_pos-1;i<=x_pos+1;i++){
                for(int j=y_pos-1;j<=y_pos+1;j++){
                    if(i==-1||j==-1||i==b->get_row()||j==b->get_col()){//overflow
                        //continue;
                    }else if(b->p[i][j].get_boom()==0){
                        Fire_OnPropertyChanged("block");
                        b->bset_show(i, j);
                        b->reset_visit(i, j);

                    }
                }
            }
        }else;
        return 1;
    }
}
bool MSDataModel::rightclick(int x_pos, int y_pos){
    if(b->p[x_pos][y_pos].get_show()==0){//rightclick on block unvisited
        //blank->flag->mark->blank
        if(b->p[x_pos][y_pos].get_flag()==0 && b->p[x_pos][y_pos].get_mark()==0){
            b->p[x_pos][y_pos].set_flag(1);
            b->p[x_pos][y_pos].set_mark(0);
            b->change_flag_num(1);//blank->flag
        }else if(b->p[x_pos][y_pos].get_flag()==1 && b->p[x_pos][y_pos].get_mark()==0){
            b->p[x_pos][y_pos].set_flag(0);
            b->p[x_pos][y_pos].set_mark(1);
            b->change_flag_num(-1);//flag->mark
        }else if(b->p[x_pos][y_pos].get_flag()==0 && b->p[x_pos][y_pos].get_mark()==1){
            b->p[x_pos][y_pos].set_flag(0);
            b->p[x_pos][y_pos].set_mark(0);//mark->blank
        }
		Fire_OnPropertyChanged("block");
    }else if(b->p[x_pos][y_pos].get_show()==1){//rightclick on block visited
        //like leftclick
        int cnt=0;
        for(int i=x_pos-1;i<=x_pos+1;i++){
            for(int j=y_pos-1;j<=y_pos+1;j++){
                if(i==-1||j==-1||i==b->get_row()||j==b->get_col()){//overflow
                    //continue;
                }else if(b->p[i][j].get_flag()==1){
                    cnt++;
                }
            }
        }
        if(cnt==b->p[x_pos][y_pos].get_sur()){//all booms around it has been flaged
            for(int i=x_pos-1;i<=x_pos+1;i++){
                for(int j=y_pos-1;j<=y_pos+1;j++){
                    if(i==-1||j==-1||i==b->get_row()||j==b->get_col()){//overflow
                        //continue;
                    }else if(b->p[i][j].get_boom()==0){
                        b->bset_show(i, j);
                        b->reset_visit(i, j);
                        Fire_OnPropertyChanged("block");
                    }
                }
            }
        }else;
    }

    //only after rightclick we can win the game
    //boom==flag
    int match_num=0;//the num of blocks which are flagged correctly
    int flag_num=0;//the num of blocks which are flagged,may false.
    for(int i=0; i<b->get_row(); i++){
        for(int j=0; j<b->get_col(); j++){
            if(b->p[i][j].get_flag()==1){
                if(b->p[i][j].get_boom()==1){
                    match_num++;
                }
                flag_num++;
            }
        }
    }
    //win
    if((match_num==b->get_boom_num())&&(flag_num==b->get_boom_num())){
        //all booms have been flagged;all flags are correct
        b->set_play(0);
        b->set_win(1);
        Fire_OnPropertyChanged("win");
        b->set_lock(1);

    }
    return 1;
}


bool MSDataModel::resetblock(SETTING setting, int row, int col, int boom_num){
    if(setting == JUNIOR){
        b->re_construct(8,8,10);
        b->set_setting(JUNIOR);
    }
    if(setting == MIDDLE){
        b->re_construct(16,16,40);
        b->set_setting(MIDDLE);
    }
    if(setting == SENIOR){
        b->re_construct(16,32,99);
        b->set_setting(SENIOR);
    }
    //customize the map with 3 input:row col boom
    if(setting == CUSTOM){
        b->re_construct(row, col, boom_num);
        b->set_setting(CUSTOM);
    }
    Fire_OnPropertyChanged("restart");
	return true;
}

bool MSDataModel::rankadd(UserParameter u){//add new user to the rank list
    //sort the user in file by time using sort();
    std::vector<UserParameter> v_user;
    v_user.push_back(u);

    //jugde which model this user is in
    if(b->get_setting()==JUNIOR){
        std::ifstream file1("JUNIOR");
        if(!file1){
            qDebug()<<"can't read the file JUNIOR";
        }else{
            while(file1>>u.name && file1>>u.time){
                v_user.push_back(u);
            }
        }
        sort(v_user.begin(),v_user.end(),ranksort);
        file1.close();//read finished

        std::ofstream file2("JUNIOR");
        if(!file2){
            qDebug()<<"can't write the file JUNIOR";
        }else{
            for(std::vector<UserParameter>::iterator it=v_user.begin(); it!= v_user.end(); it++){
                file2<<it->name<<"   "<<it->time<<std::endl;
            }
        }
        file2.close();//write finished
    }

    if(b->get_setting()==MIDDLE){
        std::ifstream file1("MIDDLE");
        if(!file1){
            qDebug()<<"can't read the file MIDDLE";
        }else{
            while(file1>>u.name && file1>>u.time){
                v_user.push_back(u);
            }
        }
        sort(v_user.begin(),v_user.end(),ranksort);
        file1.close();//read finished

        std::ofstream file2("MIDDLE");
        if(!file2){
            qDebug()<<"can't write the file MIDDLE";
        }else{
            for(std::vector<UserParameter>::iterator it=v_user.begin(); it != v_user.end(); it++){
                file2<<it->name<<"   "<<it->time<<std::endl;
            }
        }
        file2.close();//write finished
    }

    if(b->get_setting()==SENIOR){
        std::ifstream file1("SENIOR");
        if(!file1){
            qDebug()<<"can't read the file SENIOR";
        }else{
            while(file1>>u.name && file1>>u.time){
                v_user.push_back(u);
            }
        }
        sort(v_user.begin(),v_user.end(),ranksort);
        file1.close();//read finished

        std::ofstream file2("SENIOR");
        if(!file2){
            qDebug()<<"can't write the file SENIOR";
        }else{
            for(std::vector<UserParameter>::iterator it=v_user.begin(); it != v_user.end(); it++){
                file2<<it->name<<"   "<<it->time<<std::endl;
            }
        }
        file2.close();//write finished
    }
    return 0;
}
