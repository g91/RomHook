#pragma once

#include <string>
#include <functional>
#include <vector>
#include <map>
#include <ostream>

class CommandHandler;
class ResponseManager;
class RequestManager;
class StateManager;

enum Disposition {
    DispositionSubmitted,
    DispositionNotSubmitted,
    DispositionQuit,
};
class Command
{
public:
    typedef std::mem_fun1_t<Disposition, CommandHandler, const std::vector<std::string> &> ExecuteFunction;
public:
    Command(const std::string &name, const ExecuteFunction &execFunction, const std::string &usage) : 
      m_executeFunction(execFunction)
    {
        m_name = name;
        m_usage = usage;
    }

    const ExecuteFunction &GetExecuteFunction() const
    {
        return m_executeFunction;
    }
    const std::string &GetUsage() const
    {
        return m_usage;
    }
private:
    std::string m_name;
    ExecuteFunction m_executeFunction;
    std::string m_usage;
};

class CommandHandler
{
public:
    CommandHandler(std::ostream &stdcout, std::ostream &stdcerr, RequestManager *reqMgr, 
        ResponseManager *respMgr, StateManager *stateMgr);
    
    ~CommandHandler();

    Disposition Execute(const std::vector<std::string> &args);

private:
    Disposition initlogging(const std::vector<std::string> &cmd);
    Disposition usage(const std::vector<std::string> &cmd);
    Disposition init(const std::vector<std::string> &args);
    Disposition shutdown(const std::vector<std::string> &args);
    Disposition login(const std::vector<std::string> &args);
    Disposition authtokenlogin(const std::vector<std::string> &args);
    Disposition anonymouslogin(const std::vector<std::string> &cmd);
    Disposition logout(const std::vector<std::string> &args);
    Disposition loginprops(const std::vector<std::string> &args);
    Disposition sgcreate(const std::vector<std::string> &args);
    Disposition sgterminate(const std::vector<std::string> &args);
    Disposition sgaddsession(const std::vector<std::string> &args);
    Disposition sgremovesession(const std::vector<std::string> &args);
    Disposition sgsetfocus(const std::vector<std::string> &args);
    Disposition sgunsetfocus(const std::vector<std::string> &args);
    Disposition sgresetfocus(const std::vector<std::string> &args);
    Disposition sgsettx(const std::vector<std::string> &args);
    Disposition sgsettxall(const std::vector<std::string> &args);
    Disposition sgsettxnone(const std::vector<std::string> &args);
    Disposition createsession(const std::vector<std::string> &args);
    Disposition mediaconnect(const std::vector<std::string> &args);
    Disposition mediadisconnect(const std::vector<std::string> &args);
    Disposition textconnect(const std::vector<std::string> &args);
    Disposition textdisconnect(const std::vector<std::string> &args);
    Disposition terminatesession(const std::vector<std::string> &args);
    Disposition sessionmute(const std::vector<std::string> &args);
    Disposition sessionvol(const std::vector<std::string> &args);
    Disposition getsessionfonts(const std::vector<std::string> &args);
    Disposition gettemplatefonts(const std::vector<std::string> &args);
    Disposition setvoicefont(const std::vector<std::string> &args);
    Disposition call(const std::vector<std::string> &args);
    Disposition deprecatedanswer(const std::vector<std::string> &args);
    Disposition answer(const std::vector<std::string> &args);
    Disposition hangup(const std::vector<std::string> &args);
    Disposition createchannel(const std::vector<std::string> &args);
    Disposition updatechannel(const std::vector<std::string> &args);
    Disposition deletechannel(const std::vector<std::string> &args);
    Disposition getfavs(const std::vector<std::string> &args);
    Disposition setfav(const std::vector<std::string> &args);
    Disposition deletefav(const std::vector<std::string> &args);
    Disposition setfavgroup(const std::vector<std::string> &args);
    Disposition deletefavgroup(const std::vector<std::string> &args);
    Disposition getchannelinfo(const std::vector<std::string> &args);
    Disposition searchchannels(const std::vector<std::string> &args);
    Disposition searchaccounts(const std::vector<std::string> &args);
    Disposition modmuteall(const std::vector<std::string> &args);
    Disposition modmute(const std::vector<std::string> &args);
    Disposition ban(const std::vector<std::string> &args);
    Disposition getbannedlist(const std::vector<std::string> &args);
    Disposition kick(const std::vector<std::string> &args);
    Disposition lock(const std::vector<std::string> &args);
    Disposition unlock(const std::vector<std::string> &args);
    Disposition localusermute(const std::vector<std::string> &args);
    Disposition localuservolume(const std::vector<std::string> &args);
    Disposition addmoderator(const std::vector<std::string> &args);
    Disposition removemoderator(const std::vector<std::string> &args);
    Disposition getmoderators(const std::vector<std::string> &args);
    Disposition addacl(const std::vector<std::string> &args);
    Disposition removeacl(const std::vector<std::string> &args);
    Disposition getacl(const std::vector<std::string> &args);
    Disposition changechannelowner(const std::vector<std::string> &args);
    Disposition senddata(const std::vector<std::string> &args);
    Disposition getparts(const std::vector<std::string> &args);
    Disposition audioinfo(const std::vector<std::string> &args);
    Disposition speakervol(const std::vector<std::string> &args);
    Disposition speakermute(const std::vector<std::string> &args);
    Disposition micvol(const std::vector<std::string> &args);
    Disposition micmute(const std::vector<std::string> &args);
    Disposition movetoorigin(const std::vector<std::string> &args);
    Disposition moveleft(const std::vector<std::string> &args);
    Disposition moveright(const std::vector<std::string> &args);
    Disposition moveforward(const std::vector<std::string> &args);
    Disposition moveback(const std::vector<std::string> &args);
    Disposition moveup(const std::vector<std::string> &args);
    Disposition movedown(const std::vector<std::string> &args);
    Disposition turnleft45(const std::vector<std::string> &args);
    Disposition turnright45(const std::vector<std::string> &args);
    Disposition sessionpos(const std::vector<std::string> &args);
    Disposition setbuddy(const std::vector<std::string> &args);
    Disposition deletebuddy(const std::vector<std::string> &args);
    Disposition setbuddygroup(const std::vector<std::string> &args);
    Disposition deletebuddygroup(const std::vector<std::string> &args);
    Disposition createblockrule(const std::vector<std::string> &args);
    Disposition deleteblockrule(const std::vector<std::string> &args);
    Disposition listblockrules(const std::vector<std::string> &args);
    Disposition createautoacceptrule(const std::vector<std::string> &args);
    Disposition deleteautoacceptrule(const std::vector<std::string> &args);
    Disposition listautoacceptrules(const std::vector<std::string> &args);
    Disposition subscriptionreply(const std::vector<std::string> &args);
    Disposition sendmsg(const std::vector<std::string> &args);
    Disposition setpresence(const std::vector<std::string> &args);
    Disposition senddtmf(const std::vector<std::string> &args);
    Disposition sendnotification(const std::vector<std::string> &args);
    Disposition networktest(const std::vector<std::string> &args);
    Disposition recstart(const std::vector<std::string> &args);
    Disposition recstop(const std::vector<std::string> &args);
    Disposition listrenderdevs(const std::vector<std::string> &args);
    Disposition listcapturedevs(const std::vector<std::string> &args);
    Disposition setrenderdev(const std::vector<std::string> &args);
    Disposition setcapturedev(const std::vector<std::string> &args);
    Disposition setdefaultrenderdev(const std::vector<std::string> &args);
    Disposition setdefaultcapturedev(const std::vector<std::string> &args);
    Disposition renderaudiostart(const std::vector<std::string> &args);
    Disposition renderaudiofrombufferstart(const std::vector<std::string> &args);
    Disposition renderaudiostop(const std::vector<std::string> &args);
    Disposition settuningspeakervol(const std::vector<std::string> &args);
    Disposition settuningmicvol(const std::vector<std::string> &args);
    Disposition gettuningspeakervol(const std::vector<std::string> &args);
    Disposition gettuningmicvol(const std::vector<std::string> &args);
    Disposition captureaudiostart(const std::vector<std::string> &args);
    Disposition captureaudiotobufferstart(const std::vector<std::string> &args);
    Disposition captureaudiostop(const std::vector<std::string> &args);
    Disposition updateaccount(const std::vector<std::string> &args);
    Disposition getaccount(const std::vector<std::string> &args);
    Disposition sendsms(const std::vector<std::string> &args);
    Disposition setidletimeout(const std::vector<std::string> &args);
    Disposition bindkey(const std::vector<std::string> &args);
    Disposition resetpw(const std::vector<std::string> &args);
    Disposition createaccount1(const std::vector<std::string> &args);
    Disposition createaccount2(const std::vector<std::string> &args);
    Disposition setvadproperties(const std::vector<std::string> &args);
    Disposition getvadproperties(const std::vector<std::string> &args);
    Disposition injectaudiostart(const std::vector<std::string> &args);
    Disposition injectaudiorestart(const std::vector<std::string> &args);
    Disposition injectaudiostop(const std::vector<std::string> &args);
    Disposition listaudiobuffers(const std::vector<std::string> &args);
    Disposition removeaudiobuffer(const std::vector<std::string> &args);
    Disposition exportaudiobuffer(const std::vector<std::string> &args);
    Disposition webcall(const std::vector<std::string> &args);
    Disposition renderaudiomodify(const std::vector<std::string> &args);
    Disposition debuglevel(const std::vector<std::string> &cmd);
    Disposition dump(const std::vector<std::string> &cmd);
    Disposition dance(const std::vector<std::string> &cmd);
    Disposition enablevvs(const std::vector<std::string> &cmd);
    Disposition disablevvs(const std::vector<std::string> &cmd);
    Disposition state(const std::vector<std::string> &cmd);
    Disposition printUsage(const std::string &cmd) const;
    bool validateInt(const std::string &command, const std::string &param, int &val) const;
    bool validateDouble(const std::string &command, const std::string &param, double &val) const;

    typedef std::map<std::string, Command> CommandMap;

    CommandMap m_commands;
    std::ostream &cout;
    std::ostream &cerr;
    ResponseManager *m_respMgr;
    RequestManager *m_reqMgr;
    StateManager *m_stateMgr;
};
