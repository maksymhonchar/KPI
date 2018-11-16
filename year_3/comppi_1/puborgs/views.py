import json

from django.db.models.query import QuerySet
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt

from .models import Certificate, Location, Founder, GoverningBody, SubDivision, Organization, ActionReport
from .models import OrgsModelsJSONEncoder
from .modelschoices.locations import LOCATIONSREGIONCHOICES
from .modelschoices.orgadditional import ORGSTATUSCHOICES, ORGORIENTATIONCHOICES, ORGTYPECHOICES
from .modelschoices.reports import REPACTIONCHOICES


@method_decorator(csrf_exempt, name='dispatch')
def apisearchorg(req):
    if req.method == 'GET':
        json_get_response = {
            'locations_region_choices': LOCATIONSREGIONCHOICES,
            'org_status_choices': ORGSTATUSCHOICES,
            'org_orientation_choices': ORGORIENTATIONCHOICES,
            'org_type_choices': ORGTYPECHOICES,
            'default_choice': 'NONE'
        }
        return JsonResponse(json_get_response, safe=False)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        raw_search_fields = json.loads(req_params)
        allorgs = Organization.objects.all()
        # Get the fields.
        reg_num = raw_search_fields.get('reg_num', None)
        naming = raw_search_fields.get('naming', None)
        edrpou = raw_search_fields.get('edrpou', None)
        owner_edrpou = raw_search_fields.get('owner_edrpou', None)
        cert_num = raw_search_fields.get('cert_num', None)
        cert_issue_date = raw_search_fields.get('cert_issue_date', None)
        loc_region = raw_search_fields.get('loc_region', None)
        loc_district = raw_search_fields.get('loc_district', None)
        loc_locality = raw_search_fields.get('loc_locality', None)
        loc_street = raw_search_fields.get('loc_street', None)
        loc_building = raw_search_fields.get('loc_building', None)
        status = raw_search_fields.get('status', None)
        orgtype = raw_search_fields.get('type', None)
        orientation = raw_search_fields.get('orientation', None)
        # Start a search.
        result = None
        if reg_num is not None:
            if isinstance(result, QuerySet):
                result = result.filter(pk=reg_num)
            else:
                result = Organization.objects.filter(pk=reg_num)
        if naming is not None:
            if isinstance(result, QuerySet):
                result = result.filter(full_naming__icontains=naming)
            else:
                result = Organization.objects.filter(full_naming__icontains=naming)
        if edrpou is not None:
            if isinstance(result, QuerySet):
                result = result.filter(edrpou=edrpou)
            else:
                result = Organization.objects.filter(edrpou=edrpou)
        if owner_edrpou is not None:
            if isinstance(result, QuerySet):
                result = result.filter(owner_edrpou=owner_edrpou)
            else:
                result = Organization.objects.filter(owner_edrpou=owner_edrpou)
        if cert_num is not None:
            if isinstance(result, QuerySet):
                result = result.filter(certificate=cert_num)
            else:
                result = Organization.objects.filter(certificate=cert_num)
        if cert_issue_date is not None:
            for org in allorgs:
                org_certificate = org.certificate
                if org_certificate.issue_date == cert_issue_date:
                    if isinstance(result, QuerySet):
                        result |= result.filter(Organization.objects.get(pk=org.pk))
                    else:
                        result = Organization.objects.get(pk=org.pk)
        if loc_region is not None:
            for org in allorgs:
                org_location = org.location
                if org_location.region == loc_region:
                    if isinstance(result, QuerySet):
                        result |= result.filter(Organization.objects.get(pk=org.pk))
                    else:
                        result = Organization.objects.get(pk=org.pk)
        if loc_building is not None:
            for org in allorgs:
                org_location = org.location
                if org_location.building == loc_building:
                    if isinstance(result, QuerySet):
                        result |= result.filter(Organization.objects.get(pk=org.pk))
                    else:
                        result = Organization.objects.get(pk=org.pk)
        if loc_district is not None:
            for org in allorgs:
                org_location = org.location
                if org_location.district == loc_district:
                    if isinstance(result, QuerySet):
                        result |= result.filter(Organization.objects.get(pk=org.pk))
                    else:
                        result = Organization.objects.get(pk=org.pk)
        if loc_locality is not None:
            for org in allorgs:
                org_location = org.location
                if org_location.locality == loc_locality:
                    if isinstance(result, QuerySet):
                        result |= result.filter(Organization.objects.get(pk=org.pk))
                    else:
                        result = Organization.objects.get(pk=org.pk)
        if loc_street is not None:
            for org in allorgs:
                org_location = org.location
                if org_location.street == loc_street:
                    if isinstance(result, QuerySet):
                        result |= result.filter(Organization.objects.get(pk=org.pk))
                    else:
                        result = Organization.objects.get(pk=org.pk)
        if status is not None:
            if isinstance(result, QuerySet):
                result = result.filter(status=status)
            else:
                result = Organization.objects.filter(status=status)
        if orgtype is not None:
            if isinstance(result, QuerySet):
                result = result.filter(type=orgtype)
            else:
                result = Organization.objects.filter(type=orgtype)
        if orientation is not None:
            if isinstance(result, QuerySet):
                result = result.filter(orientation=orientation)
            else:
                result = Organization.objects.filter(orientation=orientation)
        # Create a resulting json response.
        json_search_response = {
            'result': result,
            'params': raw_search_fields
        }
        return JsonResponse(json_search_response, safe=False, encoder=Json)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apimanageorg(req):
    if req.method == 'GET':
        org_fields = req.GET
        org_id = org_fields.get('org_id')
        org_instance = get_object_or_404(Organization, pk=org_id)
        json_get_response = {
            'org_inst': org_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        org_fields = json.loads(req_params)
        created_by = org_fields.get('created_by')
        certificate = org_fields.get('certificate')
        location = org_fields.get('location')
        orgtype = org_fields.get('type')
        orientation = org_fields.get('orientation')
        status = org_fields.get('status')
        founders_ids_list = org_fields.get('founders_ids_list')
        governing_bodies_ids_list = org_fields.get('governing_bodies_ids_list')
        separated_subdivisions_ids_list = org_fields.get('separated_subdivisions_ids_list')
        full_naming = org_fields.get('full_naming')
        short_naming = org_fields.get('short_naming')
        edrpou = org_fields.get('edrpou')
        owner_edrpou = org_fields.get('owner_edrpou')
        foreign_naming = org_fields.get('foreign_naming')
        organiz_pravov_form = org_fields.get('organiz_pravov_form')
        registration_state = org_fields.get('registration_state')
        entrepreneurial_activity = org_fields.get('entrepreneurial_activity')
        registration_date = org_fields.get('registration_date')
        feedback = org_fields.get('feedback')
        new_org_inst = Organization(
            created_by=created_by,
            certificate=certificate,
            location=location,
            type=orgtype,
            orientation=orientation,
            status=status,
            founders_ids_list=founders_ids_list,
            governing_bodies_ids_list=governing_bodies_ids_list,
            separated_subdivisions_ids_list=separated_subdivisions_ids_list,
            full_naming=full_naming,
            short_naming=short_naming,
            edrpou=edrpou,
            owner_edrpou=owner_edrpou,
            foreign_naming=foreign_naming,
            organiz_pravov_form=organiz_pravov_form,
            registration_state=registration_state,
            entrepreneurial_activity=entrepreneurial_activity,
            registration_date=registration_date,
            feedback=feedback
        )
        new_org_inst.save()
        json_post_response = {
            'new_org_inst': new_org_inst
        }
        return JsonResponse(json_post_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        org_fields = json.loads(req_params)
        org_id = org_fields.get('org_id')
        created_by = org_fields.get('created_by')
        certificate = org_fields.get('certificate')
        location = org_fields.get('location')
        orgtype = org_fields.get('type')
        orientation = org_fields.get('orientation')
        status = org_fields.get('status')
        founders_ids_list = org_fields.get('founders_ids_list')
        governing_bodies_ids_list = org_fields.get('governing_bodies_ids_list')
        separated_subdivisions_ids_list = org_fields.get('separated_subdivisions_ids_list')
        full_naming = org_fields.get('full_naming')
        short_naming = org_fields.get('short_naming')
        edrpou = org_fields.get('edrpou')
        owner_edrpou = org_fields.get('owner_edrpou')
        foreign_naming = org_fields.get('foreign_naming')
        organiz_pravov_form = org_fields.get('organiz_pravov_form')
        registration_state = org_fields.get('registration_state')
        entrepreneurial_activity = org_fields.get('entrepreneurial_activity')
        registration_date = org_fields.get('registration_date')
        feedback = org_fields.get('feedback')
        # Get created Organization instance to update.
        upd_org_inst = get_object_or_404(Organization, pk=org_id)
        upd_org_inst.created_by = created_by
        upd_org_inst.certificate = certificate
        upd_org_inst.location = location
        upd_org_inst.orgtype = orgtype
        upd_org_inst.orientation = orientation
        upd_org_inst.status = status
        upd_org_inst.founders_ids_list = founders_ids_list
        upd_org_inst.governing_bodies_ids_list = governing_bodies_ids_list
        upd_org_inst.separated_subdivisions_ids_list = separated_subdivisions_ids_list
        upd_org_inst.full_naming = full_naming
        upd_org_inst.short_naming = short_naming
        upd_org_inst.edrpou = edrpou
        upd_org_inst.owner_edrpou = owner_edrpou
        upd_org_inst.foreign_naming = foreign_naming
        upd_org_inst.organiz_pravov_form = organiz_pravov_form
        upd_org_inst.registration_state = registration_state
        upd_org_inst.entrepreneurial_activity = entrepreneurial_activity
        upd_org_inst.registration_date = registration_date
        upd_org_inst.feedback = feedback
        upd_org_inst.save()
        json_put_response = {
            'upd_org_inst': upd_org_inst
        }
        return JsonResponse(json_put_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        org_fields = json.loads(req_params)
        org_id = org_fields.get('org_id')
        del_org_inst = get_object_or_404(Organization, pk=org_id)
        del_org_inst.delete()
        json_delete_response = {
            'deleted_id': org_id
        }
        return JsonResponse(json_delete_response, safe=False, encoder=OrgsModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apimanagecertificate(req):
    if req.method == 'GET':
        cert_fields = req.GET
        cert_id = cert_fields.get('cert_id')
        cert_instance = get_object_or_404(Certificate, pk=cert_id)
        json_get_response = {
            'cert_inst': cert_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        cert_fields = json.loads(req_params)
        issue_date = cert_fields.get('issue_date')
        new_cert_inst = Certificate(issue_date=issue_date)
        new_cert_inst.save()
        json_post_response = {
            'new_cert_inst': new_cert_inst
        }
        return JsonResponse(json_post_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        cert_fields = json.loads(req_params)
        cert_id = cert_fields.get('cert_id')
        issue_date = cert_fields.get('issue_date')
        upd_cert_inst = get_object_or_404(Certificate, pk=cert_id)
        upd_cert_inst.issue_date = issue_date
        upd_cert_inst.save()
        json_put_response = {
            'upd_cert_inst': upd_cert_inst
        }
        return JsonResponse(json_put_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        cert_fields = json.loads(req_params)
        cert_id = cert_fields.get('cert_id')
        del_cert_inst = get_object_or_404(Certificate, pk=cert_id)
        del_cert_inst.delete()
        json_delete_response = {
            'deleted_id': cert_id
        }
        return JsonResponse(json_delete_response, safe=False, encoder=OrgsModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apimanagelocation(req):
    if req.method == 'GET':
        loc_fields = req.GET
        loc_id = loc_fields.get('loc_id')
        loc_instance = get_object_or_404(Location, pk=loc_id)
        json_get_response = {
            'loc_inst': loc_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        loc_fields = json.loads(req_params)
        region = loc_fields.get('region')
        district = loc_fields.get('district')
        locality = loc_fields.get('locality')
        street = loc_fields.get('street')
        building = loc_fields.get('building')
        new_loc_inst = Location(
            region=region,
            district=district,
            locality=locality,
            street=street,
            building=building,
        )
        new_loc_inst.save()
        json_post_response = {
            'new_loc_inst': new_loc_inst
        }
        return JsonResponse(json_post_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        loc_fields = json.loads(req_params)
        loc_id = loc_fields.get('loc_id')
        region = loc_fields.get('region')
        district = loc_fields.get('district')
        locality = loc_fields.get('locality')
        street = loc_fields.get('street')
        building = loc_fields.get('building')
        upd_loc_inst = get_object_or_404(Location, pk=loc_id)
        upd_loc_inst.region = region
        upd_loc_inst.district = district
        upd_loc_inst.locality = locality
        upd_loc_inst.street = street
        upd_loc_inst.building = building
        upd_loc_inst.save()
        json_put_response = {
            'upd_loc_inst': upd_loc_inst
        }
        return JsonResponse(json_put_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        loc_fields = json.loads(req_params)
        loc_id = loc_fields.get('lod_id')
        del_loc_inst = get_object_or_404(Location, pk=loc_id)
        del_loc_inst.delete()
        json_delete_response = {
            'deleted_id': loc_id
        }
        return JsonResponse(json_delete_response, safe=False, encoder=OrgsModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apimanagefounder(req):
    if req.method == 'GET':
        fdr_fields = req.GET
        fdr_id = fdr_fields.get('fdr_id')
        fdr_instance = get_object_or_404(Founder, pk=fdr_id)
        json_get_response = {
            'fdr_inst': fdr_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        fdr_fields = json.loads(req_params)
        name = fdr_fields.get('name')
        surname = fdr_fields.get('surname')
        new_fdr_inst = Founder(name=name, surname=surname)
        new_fdr_inst.save()
        json_post_response = {
            'new_fdr_inst': new_fdr_inst
        }
        return JsonResponse(json_post_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        fdr_fields = json.loads(req_params)
        fdr_id = fdr_fields.get('fdr_id')
        name = fdr_fields.get('name')
        surname = fdr_fields.get('surname')
        upd_fdr_inst = get_object_or_404(Founder, pk=fdr_id)
        upd_fdr_inst.name = name
        upd_fdr_inst.surname = surname
        upd_fdr_inst.save()
        json_put_response = {
            'upd_fdr_inst': upd_fdr_inst
        }
        return JsonResponse(json_put_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        fdr_fields = json.loads(req_params)
        fdr_id = fdr_fields.get('fdr_id')
        del_fdr_inst = get_object_or_404(Founder, pk=fdr_id)
        del_fdr_inst.delete()
        json_delete_response = {
            'deleted_id': fdr_id
        }
        return JsonResponse(json_delete_response, safe=False, encoder=OrgsModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apimanagegovbody(req):
    if req.method == 'GET':
        gb_fields = req.GET
        gb_id = gb_fields.get('gb_id')
        gb_instance = get_object_or_404(GoverningBody, pk=gb_id)
        json_get_response = {
            'gb_inst': gb_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        gb_fields = json.loads(req_params)
        name = gb_fields.get('name')
        surname = gb_fields.get('surname')
        position = gb_fields.get('position')
        restrictions = gb_fields.get('restrictions')
        new_gb_inst = GoverningBody(name=name, surname=surname, position=position, restrictions=restrictions)
        new_gb_inst.save()
        json_post_response = {
            'new_gb_inst': new_gb_inst
        }
        return JsonResponse(json_post_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        gb_fields = json.loads(req_params)
        gb_id = gb_fields.get('gb_id')
        name = gb_fields.get('name')
        surname = gb_fields.get('surname')
        position = gb_fields.get('position')
        restrictions = gb_fields.get('restrictions')
        upd_gb_inst = get_object_or_404(GoverningBody, pk=gb_id)
        upd_gb_inst.name = name
        upd_gb_inst.surname = surname
        upd_gb_inst.position = position
        upd_gb_inst.restrictions = restrictions
        upd_gb_inst.save()
        json_put_response = {
            'upd_gb_inst': upd_gb_inst
        }
        return JsonResponse(json_put_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        gb_fields = json.loads(req_params)
        gb_id = gb_fields.get('gb_id')
        del_gb_inst = get_object_or_404(GoverningBody, pk=gb_id)
        del_gb_inst.delete()
        json_delete_response = {
            'deleted_id': gb_id
        }
        return JsonResponse(json_delete_response, safe=False, encoder=OrgsModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apimanagesubdiv(req):
    if req.method == 'GET':
        subd_fields = req.GET
        subd_id = subd_fields.get('subd_id')
        subd_instance = get_object_or_404(SubDivision, pk=subd_id)
        json_get_response = {
            'subd_inst': subd_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        subd_fields = json.loads(req_params)
        location = subd_fields.get('location')
        full_name = subd_fields.get('full_name')
        registration_state = subd_fields.get('registration_state')
        manager_full_name = subd_fields.get('manager_full_name')
        last_change_datetime = subd_fields.get('last_change_datetime')
        new_subd_inst = SubDivision(
            location=location,
            full_name=full_name,
            registration_state=registration_state,
            manager_full_name=manager_full_name,
            last_change_datetime=last_change_datetime
        )
        new_subd_inst.save()
        json_post_response = {
            'new_subd_inst': new_subd_inst
        }
        return JsonResponse(json_post_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        subd_fields = json.loads(req_params)
        subd_id = subd_fields.get('subd_id')
        location = subd_fields.get('location')
        full_name = subd_fields.get('full_name')
        registration_state = subd_fields.get('registration_state')
        manager_full_name = subd_fields.get('manager_full_name')
        last_change_datetime = subd_fields.get('last_change_datetime')
        upd_subd_inst = get_object_or_404(SubDivision, pk=subd_id)
        upd_subd_inst.location = location
        upd_subd_inst.full_name = full_name
        upd_subd_inst.registration_state = registration_state
        upd_subd_inst.manager_full_name = manager_full_name
        upd_subd_inst.last_change_datetime = last_change_datetime
        upd_subd_inst.save()
        json_put_response = {
            'upd_subd_inst': upd_subd_inst
        }
        return JsonResponse(json_put_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        subd_fields = json.loads(req_params)
        subd_id = subd_fields.get('subd_id')
        del_subd_inst = get_object_or_404(SubDivision, pk=subd_id)
        del_subd_inst.delete()
        json_delete_response = {
            'deleted_id': subd_id
        }
        return JsonResponse(json_delete_response, safe=False, encoder=OrgsModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apisearchreport(req):
    if req.method == 'GET':
        json_get_response = {
            'action_choices': REPACTIONCHOICES,
            'default_choice': 'NONE'
        }
        return JsonResponse(json_get_response, safe=False)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        raw_search_fields = json.loads(req_params)
        # Get the fields.
        registrant = raw_search_fields.get('registrant', None)
        organization = raw_search_fields.get('organization', None)
        action = raw_search_fields.get('action', None)
        action_datetime = raw_search_fields.get('raw_search_fields', None)
        # Start a search.
        result = None
        if registrant is not None:
            if isinstance(result, QuerySet):
                result = result.filter(registrant=registrant)
            else:
                result = ActionReport.objects.filter(registrant=registrant)
        if organization is not None:
            if isinstance(result, QuerySet):
                result = result.filter(organization=organization)
            else:
                result = ActionReport.objects.filter(organization=organization)
        if action is not None:
            if isinstance(result, QuerySet):
                result = result.filter(action=action)
            else:
                result = ActionReport.objects.filter(action=action)
        if action_datetime is not None:
            if isinstance(result, QuerySet):
                result = result.filter(action_datetime=action_datetime)
            else:
                result = ActionReport.objects.filter(action_datetime=action_datetime)
        json_search_response = {
            'result': result,
            'params': raw_search_fields
        }
        return JsonResponse(json_search_response, safe=False, encoder=Json)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


def apimanagereport(req):
    if req.method == 'GET':
        report_fields = req.GET
        report_id = report_fields.get('report_id')
        report_instance = get_object_or_404(ActionReport, pk=report_id)
        json_get_response = {
            'report_inst': report_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        report_fields = json.loads(req_params)
        registrant = report_fields.get('registrant')
        organization = report_fields.get('organization')
        action = report_fields.get('action')
        action_datetime = report_fields.get('action_datetime')
        new_report_inst = ActionReport(
            registrant=registrant,
            organization=organization,
            action=action,
            action_datetime=action_datetime,
        )
        new_report_inst.save()
        json_post_response = {
            'new_report_inst': new_report_inst
        }
        return JsonResponse(json_post_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        report_fields = json.loads(req_params)
        report_id = report_fields.get('report_id')
        registrant = report_fields.get('registrant')
        organization = report_fields.get('organization')
        action = report_fields.get('action')
        action_datetime = report_fields.get('action_datetime')
        upd_report_inst = get_object_or_404(ActionReport, pk=report_id)
        upd_report_inst.registrant = registrant
        upd_report_inst.organization = organization
        upd_report_inst.action = action
        upd_report_inst.action_datetime = action_datetime
        upd_report_inst.save()
        json_put_response = {
            'upd_report_inst': upd_report_inst
        }
        return JsonResponse(json_put_response, safe=False, encoder=OrgsModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        report_fields = json.loads(req_params)
        report_id = report_fields.get('report_id')
        del_report_inst = get_object_or_404(ActionReport, pk=report_id)
        del_report_inst.delete()
        json_delete_response = {
            'deleted_id': report_id
        }
        return JsonResponse(json_delete_response, safe=False, encoder=OrgsModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)
