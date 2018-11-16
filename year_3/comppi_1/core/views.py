from django.contrib.auth import authenticate
from django.contrib.auth import login as auth_login
from django.contrib.auth import logout as auth_logout
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.db.models.query import QuerySet
from django.http import JsonResponse
from django.shortcuts import redirect, render

from managers.models import PubOrgAdmin, PubOrgRegistrant
from puborgs.models import ActionReport
from puborgs.models import Organization, Certificate, Location
from .forms import (
    LogInForm, SupportMsgForm,
    NewRegistrantForm, EditRegistrantForm,
    NewOrganizationForm, EditOrganizationForm,
    OrgSearchForm
)


def get_current_user_role(req):
    if req.user.is_authenticated:
        try:
            return PubOrgAdmin.objects.get(pk=req.user.id)
        except PubOrgAdmin.DoesNotExist:
            pass
        try:
            return PubOrgRegistrant.objects.get(pk=req.user.id)
        except PubOrgRegistrant.DoesNotExist:
            pass
        return None
    else:
        return None


def index(req):
    template_path = 'core/index.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
    }
    return render(req, template_path, context=render_context)


def apimap(req):
    json_response = {
        'managers': ['login/', 'logout/', 'admin/', 'registrant/'],
        'puborgs': ['searchorg/', 'org/', 'certificate/', 'founder/', 'govbody/', 'location/', 'subdiv/',
                    'searchreport/', 'report/']
    }
    return JsonResponse(json_response, safe=False)


def support(req):
    if req.method == 'POST':
        form = SupportMsgForm(req.POST)
        if form.is_valid:
            pass
    else:
        form = SupportMsgForm()
    template_path = 'core/support.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'suppform': form
    }
    return render(req, template_path, context=render_context)


def about(req):
    template_path = 'core/about.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
    }
    return render(req, template_path, context=render_context)


def login(req):
    form_err_msg = None
    if req.method == 'POST':
        form = LogInForm(req.POST)
        if form.is_valid():
            username = form.cleaned_data['username']
            password = form.cleaned_data['password']
            auth_user = authenticate(username=username, password=password)
            if auth_user is not None:
                auth_login(req, auth_user)
                current_user_role = get_current_user_role(req)
                if current_user_role.is_admin:
                    return redirect('adminindex')
                else:
                    return redirect('registrantindex')
            else:
                form_err_msg = 'Не знайдено співробітника із вказаними даними'
    else:
        form = LogInForm()
    template_path = 'auth/login.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'loginform': form,
        'formerrmsg': form_err_msg
    }
    return render(req, template_path, context=render_context)


def logout(req):
    if req.user.is_authenticated:
        auth_logout(req)
    return redirect('index')


@login_required(login_url='/login/')
def adminindex(req):
    template_path = 'orgadmin/index.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
    }
    if not render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def manageadmin(req):
    form_err_msg = None
    if req.method == 'POST':
        form = NewRegistrantForm(req.POST)
        if form.is_valid():
            username = form.cleaned_data['username']
            password = form.cleaned_data['password']
            hired_order_code = form.cleaned_data['hired_order_code']
            doc_code = form.cleaned_data['doc_code']
            credentials = form.cleaned_data['credentials']
            try:
                existing_user = User.objects.get(username=username)
                form_err_msg = 'Співробітник із такими даними вже існує: {0}'.format(existing_user.username)
            except User.DoesNotExist:
                new_user = User(username=username, password=password)
                new_user.save()
                new_registrant = PubOrgRegistrant(
                    hired_order_code=hired_order_code,
                    doc_code=doc_code,
                    credentials=credentials
                )
                new_registrant.user = new_user
                new_registrant.hired_by = get_current_user_role(req)
                new_registrant.save()
                return redirect('adminmng')
    else:
        form = NewRegistrantForm()
    all_regs = list(PubOrgRegistrant.objects.all())
    template_path = 'orgadmin/manage.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'allregs': all_regs,
        'newregform': form,
        'formerrmsg': form_err_msg,
    }
    if not render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def editregistrant(req, regid):
    try:
        reg_to_change = PubOrgRegistrant.objects.get(pk=regid)
    except PubOrgRegistrant.DoesNotExist:
        return redirect('index')
    if req.method == 'POST':
        form = EditRegistrantForm(req.POST)
        if form.is_valid():
            hired_order_code = form.cleaned_data['hired_order_code']
            doc_code = form.cleaned_data['doc_code']
            credentials = form.cleaned_data['credentials']
            reg_to_upd = PubOrgRegistrant.objects.get(pk=regid)
            reg_to_upd.hired_order_code = hired_order_code
            reg_to_upd.doc_code = doc_code
            reg_to_upd.credentials = credentials
            reg_to_upd.save()
            return redirect('adminmng')
    else:
        form = EditRegistrantForm()
        form.initial = {
            'hired_order_code': reg_to_change.hired_order_code,
            'doc_code': reg_to_change.doc_code,
            'credentials': reg_to_change.credentials,
        }
    template_path = 'orgadmin/edit.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'regtochange': reg_to_change,
        'regchangeform': form,
    }
    if not render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def deleteregistrant(req, regid):
    if not get_current_user_role(req).is_admin:
        return redirect('index')
    try:
        reg_to_delete = PubOrgRegistrant.objects.get(pk=regid)
        user_reg_to_delete = reg_to_delete.user
        reg_to_delete.delete()
        user_reg_to_delete.delete()
    except PubOrgRegistrant.DoesNotExist:
        pass
    finally:
        return redirect('adminmng')


@login_required(login_url='/login/')
def registrantindex(req):
    template_path = 'registrant/index.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
    }
    if render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def manageregistrant(req):
    form_err_msg = None
    if req.method == 'POST':
        form = NewOrganizationForm(req.POST)
        if form.is_valid():
            cert_issue_date = form.cleaned_data['cert_issue_date']
            new_cert = Certificate(issue_date=cert_issue_date)
            new_cert.save()

            loc_region = form.cleaned_data['loc_region']
            loc_district = form.cleaned_data['loc_district']
            loc_locality = form.cleaned_data['loc_locality']
            loc_street = form.cleaned_data['loc_street']
            loc_building = form.cleaned_data['loc_building']
            new_loc = Location(
                region=loc_region,
                district=loc_district,
                locality=loc_locality,
                street=loc_street,
                building=loc_building
            )
            new_loc.save()

            org_type = form.cleaned_data['org_type']
            org_orientation = form.cleaned_data['org_orientation']
            org_status = form.cleaned_data['org_status']
            org_full_naming = form.cleaned_data['org_full_naming']
            org_short_naming = form.cleaned_data['org_short_naming']
            org_foreign_naming = form.cleaned_data['org_foreign_naming']
            org_edrpou = form.cleaned_data['org_edrpou']
            org_owner_edrpou = form.cleaned_data['org_owner_edrpou']
            org_organiz_pravov_form = form.cleaned_data['org_organiz_pravov_form']
            org_registration_state = form.cleaned_data['org_registration_state']
            org_entrepreneurial_activity = form.cleaned_data['org_entrepreneurial_activity']
            org_feedback = form.cleaned_data['org_feedback']
            new_org = Organization(
                type=org_type,
                orientation=org_orientation,
                status=org_status,
                full_naming=org_full_naming,
                short_naming=org_short_naming,
                foreign_naming=org_foreign_naming,
                edrpou=org_edrpou,
                owner_edrpou=org_owner_edrpou,
                organiz_pravov_form=org_organiz_pravov_form,
                registration_state=org_registration_state,
                entrepreneurial_activity=org_entrepreneurial_activity,
                feedback=org_feedback
            )
            new_org.created_by = get_current_user_role(req)
            new_org.certificate = new_cert
            new_org.location = new_loc
            try:
                new_org.save()
                # Create update report.
                new_report = ActionReport(
                    action="n",
                )
                new_report.registrant = get_current_user_role(req)
                new_report.organization = new_org
                new_report.save()
                return redirect('manageorg', orgid=new_org.pk)
            except Exception:
                form_err_msg = 'Не вдалось створити запис про дане ГО.'
    else:
        form = NewOrganizationForm()
    template_path = 'registrant/manage.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'neworgform': form,
        'formerrmsg': form_err_msg,
    }
    if render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def editorg(req, orgid):
    try:
        org_to_change = Organization.objects.get(pk=orgid)
    except Organization.DoesNotExist:
        return redirect('index')
    if req.method == 'POST':
        form = EditOrganizationForm(req.POST)
        if form.is_valid():
            org_type = form.cleaned_data['org_type']
            org_orientation = form.cleaned_data['org_orientation']
            org_status = form.cleaned_data['org_status']
            org_full_naming = form.cleaned_data['org_full_naming']
            org_short_naming = form.cleaned_data['org_short_naming']
            org_foreign_naming = form.cleaned_data['org_foreign_naming']
            org_edrpou = form.cleaned_data['org_edrpou']
            org_owner_edrpou = form.cleaned_data['org_owner_edrpou']
            org_organiz_pravov_form = form.cleaned_data['org_organiz_pravov_form']
            org_registration_state = form.cleaned_data['org_registration_state']
            org_entrepreneurial_activity = form.cleaned_data['org_entrepreneurial_activity']
            org_feedback = form.cleaned_data['org_feedback']
            # Create organization to update.
            org_to_upd = Organization.objects.get(pk=orgid)
            org_to_upd.type = org_type
            org_to_upd.orientation = org_orientation
            org_to_upd.status = org_status
            org_to_upd.full_naming = org_full_naming
            org_to_upd.short_naming = org_short_naming
            org_to_upd.foreign_naming = org_foreign_naming
            org_to_upd.edrpou = org_edrpou
            org_to_upd.owner_edrpou = org_owner_edrpou
            org_to_upd.organiz_pravov_form = org_organiz_pravov_form
            org_to_upd.registration_state = org_registration_state
            org_to_upd.entrepreneurial_activity = org_entrepreneurial_activity
            org_to_upd.feedback = org_feedback
            org_to_upd.save()
            # Create update report.
            upd_report = ActionReport(
                action="u",
            )
            upd_report.registrant = get_current_user_role(req)
            upd_report.organization = org_to_upd
            upd_report.save()
            return redirect('manageorg', orgid=orgid)
    else:
        form = EditOrganizationForm()
        form.initial = {
            'org_type': org_to_change.type,
            'org_orientation': org_to_change.orientation,
            'org_status': org_to_change.status,
            'org_full_naming': org_to_change.full_naming,
            'org_short_naming': org_to_change.short_naming,
            'org_foreign_naming': org_to_change.foreign_naming,
            'org_edrpou': org_to_change.edrpou,
            'org_owner_edrpou': org_to_change.owner_edrpou,
            'org_organiz_pravov_form': org_to_change.organiz_pravov_form,
            'org_registration_state': org_to_change.registration_state,
            'org_entrepreneurial_activity': org_to_change.entrepreneurial_activity,
            'org_feedback': org_to_change.feedback
        }
    template_path = 'registrant/edit.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'editprgform': form,
        'orgtochange': org_to_change,
    }
    if render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def change_org_active_status(req, orgid):
    try:
        org_to_change = Organization.objects.get(pk=orgid)
    except Organization.DoesNotExist:
        return redirect('index')
    if org_to_change.registration_state is True:
        org_to_change.registration_state = False
    else:
        org_to_change.registration_state = True
    org_to_change.save()
    upd_rep = ActionReport(
        action="d",
    )
    upd_rep.registrant = get_current_user_role(req)
    upd_rep.organization = org_to_change
    upd_rep.save()
    return redirect('manageorg', orgid=orgid)


def manageorg(req, orgid):
    try:
        org_to_display = Organization.objects.get(pk=orgid)
    except Organization.DoesNotExist:
        return redirect('searchorg')
    template_path = 'org/organization.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'orgtodisplay': org_to_display,
    }
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def managereport(req, reportid):
    try:
        rep_to_display = ActionReport.objects.get(pk=reportid)
    except Organization.DoesNotExist:
        return redirect('searchreportindex')
    template_path = 'report/report.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'reportinst': rep_to_display,
    }
    if not render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


@login_required(login_url='/login/')
def searchreportindex(req):
    reps_update = ActionReport.objects.filter(action="u")
    reps_new = ActionReport.objects.filter(action="n")
    reps_deactivate = ActionReport.objects.filter(action="d")
    template_path = 'report/search.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'repsupd': reps_update,
        'repsnew': reps_new,
        'repsdel': reps_deactivate
    }
    if not render_context.get('userinst').is_admin:
        return redirect('index')
    return render(req, template_path, context=render_context)


def searchorgindex(req):
    searchresult = list()
    if req.method == 'POST':
        form = OrgSearchForm(req.POST)
        if form.is_valid():
            reg_num = form.cleaned_data.get('org_idnum', None)
            print(reg_num)
            full_naming = form.cleaned_data.get('org_full_naming', None)
            print(full_naming)
            edrpou = form.cleaned_data.get('org_edrpou', None)
            print(edrpou)
            owner_edrpou = form.cleaned_data.get('org_owner_edrpou', None)
            print(owner_edrpou)
            orgtype = form.cleaned_data.get('org_type', None)
            print(orgtype)
            orientation = form.cleaned_data.get('org_orientation', None)
            print(orientation)
            status = form.cleaned_data.get('org_status', None)
            print(status)
            cert_issue_date = form.cleaned_data.get('cert_issue_date', None)
            print(cert_issue_date)
            loc_region = form.cleaned_data.get('loc_region', None)
            print(loc_region)
            loc_district = form.cleaned_data.get('loc_district', None)
            print(loc_district)
            loc_locality = form.cleaned_data.get('loc_locality', None)
            print(loc_locality)
            loc_street = form.cleaned_data.get('loc_street', None)
            print(loc_street)
            loc_building = form.cleaned_data.get('loc_building', None)
            print(loc_building)
            # Start a search.
            allorgs = Organization.objects.all()
            if reg_num is not None and reg_num is not "":
                if isinstance(searchresult, QuerySet):
                    searchresult = searchresult.filter(pk=int(reg_num))
                else:
                    searchresult = Organization.objects.filter(pk=int(reg_num))
            print(searchresult)
            if full_naming is not None and full_naming is not "":
                if isinstance(searchresult, QuerySet):
                    searchresult = searchresult.filter(full_naming__icontains=full_naming)
                else:
                    searchresult = Organization.objects.filter(full_naming__icontains=full_naming)
            print(searchresult)
            if edrpou is not None and edrpou is not "":
                if isinstance(searchresult, QuerySet):
                    searchresult = searchresult.filter(edrpou=edrpou)
                else:
                    searchresult = Organization.objects.filter(edrpou=edrpou)
            print(searchresult)
            if owner_edrpou is not None and owner_edrpou is not "":
                if isinstance(searchresult, QuerySet):
                    searchresult = searchresult.filter(owner_edrpou=owner_edrpou)
                else:
                    searchresult = Organization.objects.filter(owner_edrpou=owner_edrpou)
            print(searchresult)
            if cert_issue_date is not None and cert_issue_date is not "":
                for org in allorgs:
                    org_certificate = org.certificate
                    if org_certificate.issue_date == cert_issue_date:
                        if isinstance(searchresult, QuerySet):
                            searchresult |= searchresult.filter(Organization.objects.get(pk=org.pk))
                        else:
                            searchresult = Organization.objects.get(pk=org.pk)
            print(searchresult)
            if loc_region is not None and (loc_region is not "" or loc_region is not "NONE"):
                for org in allorgs:
                    org_location = org.location
                    if org_location.region == loc_region:
                        if isinstance(searchresult, QuerySet):
                            searchresult |= searchresult.filter(Organization.objects.get(pk=org.pk))
                        else:
                            searchresult = Organization.objects.get(pk=org.pk)
            print(searchresult)
            if loc_building is not None and loc_building is not "":
                for org in allorgs:
                    org_location = org.location
                    if org_location.building == loc_building:
                        if isinstance(searchresult, QuerySet):
                            searchresult |= searchresult.filter(Organization.objects.get(pk=org.pk))
                        else:
                            searchresult = Organization.objects.get(pk=org.pk)
            print(searchresult)
            if loc_district is not None and loc_district is not "":
                for org in allorgs:
                    org_location = org.location
                    if org_location.district == loc_district:
                        if isinstance(searchresult, QuerySet):
                            searchresult |= searchresult.filter(Organization.objects.get(pk=org.pk))
                        else:
                            searchresult = Organization.objects.get(pk=org.pk)
            print(searchresult)
            if loc_locality is not None and loc_locality is not "":
                for org in allorgs:
                    org_location = org.location
                    if org_location.locality == loc_locality:
                        if isinstance(searchresult, QuerySet):
                            searchresult |= searchresult.filter(Organization.objects.get(pk=org.pk))
                        else:
                            searchresult = Organization.objects.get(pk=org.pk)
            print(searchresult)
            if loc_street is not None and loc_street is not "":
                for org in allorgs:
                    org_location = org.location
                    if org_location.street == loc_street:
                        if isinstance(searchresult, QuerySet):
                            searchresult |= searchresult.filter(Organization.objects.get(pk=org.pk))
                        else:
                            searchresult = Organization.objects.get(pk=org.pk)
            print(searchresult)
            print("[{0}]".format(status))
            print(type(status), len(status))
            print()
            print(status is not None)
            print(status is "NONE")
            print(status is not "")
            print(status is not "NONE")
            print(status is not None and (status is not "" and status is not "NONE"))
            if status is not None and (status is not "" and not status.startswith("NONE")):
                if isinstance(searchresult, QuerySet):
                    searchresult = searchresult.filter(status=status)
                else:
                    searchresult = Organization.objects.filter(status=status)
            print(searchresult)
            print(orgtype)
            print(orgtype is not None and (orgtype is not "" and orgtype is not "NONE"))
            if orgtype is not None and (orgtype is not "" and not orgtype.startswith("NONE")):
                if isinstance(searchresult, QuerySet):
                    searchresult = searchresult.filter(type=orgtype)
                else:
                    searchresult = Organization.objects.filter(type=orgtype)
            print(searchresult)
            print(orientation)
            print(orientation is not "" and orientation is not "NONE")
            if orientation is not None and (orientation is not "" and not orientation.startswith("NONE")):
                print('hi!')
                if isinstance(searchresult, QuerySet):
                    searchresult = searchresult.filter(orientation=orientation)
                else:
                    searchresult = Organization.objects.filter(orientation=orientation)
            print(searchresult)
    else:
        form = OrgSearchForm()
    template_path = 'org/search.html'
    render_context = {
        'user': req.user,
        'userinst': get_current_user_role(req),
        'searchform': form,
        'searchresult': list(searchresult),
    }
    return render(req, template_path, context=render_context)
