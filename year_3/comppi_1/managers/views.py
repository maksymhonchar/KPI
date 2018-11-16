import json

from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User
from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt

from .models import ManagersModelsJSONEncoder
from .models import PubOrgAdmin, PubOrgRegistrant


@method_decorator(csrf_exempt, name='dispatch')
def apilogin(req):
    if req.method == 'POST':
        req_params = req.body.decode("utf-8")
        login_fields = json.loads(req_params)
        username = login_fields.get('username')
        password = login_fields.get('password')
        auth_user = authenticate(username=username, password=password)
        if auth_user is not None:
            login(req, auth_user)
            json_positive_response = {'status': True}
            return JsonResponse(json_positive_response)
        json_negative_response = {'status': False}
        return JsonResponse(json_negative_response)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


@method_decorator(csrf_exempt, name='dispatch')
def apilogout(req):
    if req.method == 'POST':
        if req.user.is_authenticated:
            saved_user = req.user
        else:
            saved_user = None
        logout(req)
        json_logout_state_response = {
            'logged_out_user': saved_user,
            'logged_out': not req.user.is_authenticated
        }
        return JsonResponse(json_logout_state_response, safe=False, encoder=ManagersModelsJSONEncoder)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


@method_decorator(csrf_exempt, name='dispatch')
def apimanageadmin(req):
    try:
        current_user_instance = req.user
        current_admin_instance = get_object_or_404(PubOrgAdmin, user=req.user.id)
    except Exception as e:
        json_err_response = {'status': 404, 'descr': 'Some exception: {0}'.format(e)}
        return JsonResponse(json_err_response)

    if req.method == 'GET':
        json_get_response = {
            'user_inst': current_user_instance,
            'admin_inst': current_admin_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=ManagersModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        post_fields = json.loads(req_params)
        username = post_fields.get('username')
        password = post_fields.get('password')
        doc_code = post_fields.get('doc_code')
        credentials = post_fields.get('credentials')
        # Create and save User instance.
        new_user_inst = User(username=username, password=password)
        new_user_inst.save()
        # Create and save PubOrgAdmin instance.
        new_puborgadmin_inst = PubOrgAdmin(
            user=new_user_inst.pk,
            doc_code=doc_code,
            credentials=credentials
        )
        new_puborgadmin_inst.save()
        # Send resulting json response.
        json_post_response = {
            'new_user_inst': new_user_inst,
            'new_admin_inst': new_puborgadmin_inst,
        }
        return JsonResponse(json_post_response, safe=False, encoder=ManagersModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        put_fields = json.loads(req_params)
        admin_id = put_fields.get('admin_id')
        doc_code = put_fields.get('doc_code')
        credentials = put_fields.get('credentials')
        # Update and save PubOrgAdmin instance.
        admin_to_update = PubOrgAdmin.objects.get(pk=admin_id)
        admin_to_update.doc_code = doc_code
        admin_to_update.credentials = credentials
        admin_to_update.save()
        # Send resulting json response.
        json_put_response = {
            'upd_admin_inst': admin_to_update
        }
        return JsonResponse(json_put_response, safe=False, encoder=ManagersModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        delete_fields = json.loads(req_params)
        admin_id = delete_fields.get('admin_id')
        admin_instance = get_object_or_404(PubOrgAdmin, pk=admin_id)
        admin_user_instance = get_object_or_404(User, pk=admin_instance.user.pk)
        admin_instance.delete()
        admin_user_instance.delete()
        json_delete_response = {
            'deleted_id': admin_id,
        }
        return JsonResponse(json_delete_response)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)


@method_decorator(csrf_exempt, name='dispatch')
def apimanageregistrant(req):
    try:
        current_user_instance = req.user
        current_registrant_instance = get_object_or_404(PubOrgRegistrant, user=req.user.id)
    except Exception as e:
        json_err_response = {'status': 404, 'descr': 'Some exception: {0}'.format(e)}
        return JsonResponse(json_err_response)

    if req.method == 'GET':
        json_get_response = {
            'user_inst': current_user_instance,
            'registrant_inst': current_registrant_instance
        }
        return JsonResponse(json_get_response, safe=False, encoder=ManagersModelsJSONEncoder)
    elif req.method == 'POST':
        req_params = req.body.decode("utf-8")
        post_fields = json.loads(req_params)
        username = post_fields.get('username')
        password = post_fields.get('password')
        hired_by = post_fields.get('hired_by')
        hired_order_code = post_fields.get('hired_order_code')
        doc_code = post_fields.get('doc_code')
        credentials = post_fields.get('credentials')
        # Create and save User instance.
        new_user_inst = User(username=username, password=password)
        new_user_inst.save()
        # Create and save PubOrgRegistrant instance.
        new_puborgregistrant_inst = PubOrgRegistrant(
            user=new_user_inst.pk,
            hired_by=hired_by,
            hired_order_code=hired_order_code,
            doc_code=doc_code,
            credentials=credentials
        )
        new_puborgregistrant_inst.save()
        # Send resulting json response.
        json_post_response = {
            'new_user_inst': new_user_inst,
            'new_registrant_inst': new_puborgregistrant_inst,
        }
        return JsonResponse(json_post_response, safe=False, encoder=ManagersModelsJSONEncoder)
    elif req.method == 'PUT':
        req_params = req.body.decode("utf-8")
        put_fields = json.loads(req_params)
        registrant_id = put_fields.get('registrant_id')
        hired_by = put_fields.get('hired_by')
        hired_order_code = put_fields.get('hired_order_code')
        doc_code = put_fields.get('doc_code')
        credentials = put_fields.get('credentials')
        # Update and save PubOrgRegistrant instance.
        registrant_to_update = PubOrgRegistrant.objects.get(pk=registrant_id)
        registrant_to_update.hired_by = hired_by
        registrant_to_update.hired_order_code = hired_order_code
        registrant_to_update.doc_code = doc_code
        registrant_to_update.credentials = credentials
        registrant_to_update.save()
        # Send resulting json response.
        json_put_response = {
            'upd_registrant_inst': registrant_to_update
        }
        return JsonResponse(json_put_response, safe=False, encoder=ManagersModelsJSONEncoder)
    elif req.method == 'DELETE':
        req_params = req.body.decode("utf-8")
        delete_fields = json.loads(req_params)
        registrant_id = delete_fields.get('registrant_id')
        registrant_instance = get_object_or_404(PubOrgRegistrant, pk=registrant_id)
        registrant_user_instance = get_object_or_404(User, pk=registrant_instance.user.pk)
        registrant_instance.delete()
        registrant_user_instance.delete()
        json_delete_response = {
            'deleted_id': registrant_id,
        }
        return JsonResponse(json_delete_response)
    json_err_response = {'status': 405, 'descr': 'method not allowed'}
    return JsonResponse(json_err_response)
