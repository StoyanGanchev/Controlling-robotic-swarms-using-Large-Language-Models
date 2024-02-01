import airsim
import math
import numpy as np

objects_dict = {
}


class AirSimWrapper:
    def __init__(self, drone_id):
        self.drone_id = drone_id
        self.drone_id = airsim.MultirotorClient()
        self.drone_id.confirmConnection()
        self.drone_id.enableApiControl(True, drone_id)
        self.drone_id.armDisarm(True, drone_id)

    def takeoff(self, drone_id):
        self.drone_id.takeoffAsync(vehicle_name = drone_id).join()

    def land(self, drone_id):
        self.drone_id.landAsync(vehicle_name = drone_id).join()

    def get_drone_position(self, drone_id):
        pose = self.drone_id.simGetVehiclePose(vehicle_name=drone_id)
        return [pose.position.x_val, pose.position.y_val, pose.position.z_val]

    def fly_to(self ,point, drone_id):
        if point[2] > 0:
            self.drone_id.moveToPositionAsync(point[0], point[1], -point[2], 5, vehicle_name=drone_id).join()
        else:
            self.drone_id.moveToPositionAsync(point[0], point[1], point[2], 5, vehicle_name=drone_id).join()

    def fly_path(self, points, drone_id):
        airsim_points = []
        for point in points:
            if point[2] > 0:
                airsim_points.append(airsim.Vector3r(point[0], point[1], -point[2]))
            else:
                airsim_points.append(airsim.Vector3r(point[0], point[1], point[2]))
        self.drone_id.moveOnPathAsync(airsim_points, 5, 120, airsim.DrivetrainType.ForwardOnly, airsim.YawMode(False, 0), 20, 1, vehicle_name=drone_id).join()

    def set_yaw(self, yaw, drone_id):
        self.drone_id.rotateToYawAsync(yaw, 5, vehicle_name=drone_id).join()

    def get_yaw(self, drone_id):
        orientation_quat = self.drone_id.simGetVehiclePose(vehicle_name=drone_id).orientation
        yaw = airsim.to_eularian_angles(orientation_quat)[2]
        return yaw

    def get_position(self, object_name):
        query_string = objects_dict[object_name] + ".*"
        object_names_ue = []
        while len(object_names_ue) == 0:
            object_names_ue = self.drone_id.simListSceneObjects(query_string)
        pose = self.drone_id.simGetObjectPose(object_names_ue[0])
        return [pose.position.x_val, pose.position.y_val, pose.position.z_val]
